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

#include <config.h>

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
      case 172: // value
      case 176: // map_value
      case 214: // socket_type
      case 217: // outbound_interface_value
      case 227: // db_type
      case 309: // hr_mode
      case 455: // ncr_protocol_value
      case 463: // replace_client_name_value
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 172: // value
      case 176: // map_value
      case 214: // socket_type
      case 217: // outbound_interface_value
      case 227: // db_type
      case 309: // hr_mode
      case 455: // ncr_protocol_value
      case 463: // replace_client_name_value
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
            case 153: // "constant string"

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 154: // "integer"

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 155: // "floating point"

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 156: // "boolean"

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 172: // value

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 176: // map_value

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 214: // socket_type

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 217: // outbound_interface_value

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 227: // db_type

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 309: // hr_mode

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 455: // ncr_protocol_value

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 463: // replace_client_name_value

#line 231 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 172: // value
      case 176: // map_value
      case 214: // socket_type
      case 217: // outbound_interface_value
      case 227: // db_type
      case 309: // hr_mode
      case 455: // ncr_protocol_value
      case 463: // replace_client_name_value
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
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 336 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 340 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 366 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 390 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 405 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 609 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 623 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1521 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1539 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1617 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1634 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 853 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1709 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 905 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1829 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1839 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1032 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1034 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1049 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1054 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1984 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2002 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1104 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1136 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1202 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2136 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1220 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1237 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1242 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2193 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1310 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2307 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2345 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1395 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2353 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1420 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2437 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2475 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2483 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2493 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2529 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2547 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2565 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2573 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2601 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2743 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2761 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2858 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2932 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1801 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1862 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3108 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3118 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1906 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1916 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3199 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1984 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 2002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3328 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 596:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3355 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3359 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -737;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     283,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,    41,    19,    42,    50,    52,    73,
      85,    89,   133,   141,   164,   175,   200,   213,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,    19,   -98,     8,    62,    31,   156,
      46,   168,    16,    34,   246,   -29,   301,    -2,  -737,   187,
     219,   230,   227,   245,  -737,  -737,  -737,  -737,  -737,   266,
    -737,    48,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   268,
     273,  -737,  -737,  -737,  -737,  -737,   306,   307,   315,   332,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
     334,  -737,  -737,  -737,    64,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,   360,  -737,    71,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,   363,   364,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,    87,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,   127,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,   251,   259,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   265,  -737,
    -737,   370,  -737,  -737,  -737,   371,  -737,  -737,   368,   376,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,   377,   380,  -737,  -737,  -737,  -737,   379,
     382,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,   149,  -737,  -737,  -737,   384,  -737,  -737,
     389,  -737,   390,   391,  -737,  -737,   394,   396,   397,  -737,
    -737,  -737,  -737,  -737,   151,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,   159,  -737,  -737,  -737,    19,    19,  -737,   249,   399,
     400,   401,   402,   403,  -737,     8,  -737,   432,   281,   282,
     435,   436,   437,   438,   439,   290,   291,   292,   293,   444,
     445,   446,   447,   448,   449,   451,   452,   453,   454,   305,
     456,   457,    62,  -737,   458,   460,   461,   311,    31,  -737,
     462,   464,   465,   468,   470,   471,   472,   326,   323,   477,
     479,   480,   482,   156,  -737,   483,    46,  -737,   484,   485,
     488,   489,   490,   491,   492,   493,  -737,   168,  -737,   494,
     495,   346,   497,   500,   502,   351,  -737,    34,   504,   353,
     354,  -737,   246,   507,   508,    39,  -737,   357,   510,   511,
     362,   513,   365,   366,   514,   517,   369,   372,   373,   520,
     522,   301,  -737,   523,    -2,  -737,  -737,  -737,   526,   524,
     525,    19,    19,    19,  -737,   527,  -737,  -737,   383,   385,
     386,   528,   530,  -737,  -737,  -737,  -737,   535,   536,   537,
     538,   539,   392,   542,   543,   544,   545,  -737,   546,   547,
    -737,   550,   181,   196,  -737,  -737,   398,   404,   405,   551,
     406,   407,   408,  -737,  -737,   206,   409,   558,   557,  -737,
     412,  -737,   550,   413,   414,   415,   416,   417,   418,   419,
    -737,   420,   421,  -737,   422,   423,   424,  -737,  -737,   425,
    -737,  -737,  -737,   426,    19,  -737,  -737,   427,   428,  -737,
     429,  -737,  -737,    17,   410,  -737,  -737,  -737,    -5,   430,
    -737,   579,  -737,    19,    62,    -2,  -737,  -737,  -737,    31,
    -737,  -737,  -737,   255,   255,   578,   580,   581,   582,  -737,
    -737,  -737,   269,   583,   584,   225,    80,   301,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   585,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   586,   503,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,   587,  -737,   160,   180,   186,  -737,  -737,  -737,  -737,
     540,   592,   593,   594,   595,  -737,  -737,   596,   597,   598,
     599,   600,  -737,   194,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,   203,  -737,   601,   602,  -737,  -737,   603,   605,
    -737,  -737,   604,   608,  -737,  -737,   606,   610,  -737,  -737,
    -737,  -737,  -737,  -737,    75,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,   120,  -737,  -737,   609,   611,  -737,   612,   613,
     614,   615,   616,   617,   233,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,   242,  -737,  -737,
    -737,   258,   433,  -737,   618,   619,  -737,  -737,   620,   622,
    -737,  -737,   621,  -737,   138,  -737,  -737,  -737,  -737,   623,
     624,   626,   627,   469,   450,   478,   481,   486,   629,   630,
     487,   496,   498,   499,   501,   255,  -737,  -737,   156,  -737,
     578,    34,  -737,   580,   246,  -737,   581,   195,  -737,   582,
     269,  -737,     7,   583,  -737,   -29,  -737,   584,   505,   506,
     509,   512,   515,   516,   225,  -737,   631,   632,    80,  -737,
    -737,  -737,   633,   635,    46,  -737,   585,   168,  -737,   586,
     638,  -737,    68,   587,  -737,    77,   518,   521,   534,  -737,
    -737,  -737,  -737,  -737,   552,   553,  -737,  -737,  -737,  -737,
    -737,  -737,   260,  -737,   636,  -737,   637,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   310,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   639,
     640,  -737,  -737,  -737,  -737,   325,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,   554,   556,  -737,  -737,   560,   327,
    -737,   641,  -737,   562,  -737,   642,  -737,  -737,  -737,  -737,
    -737,   337,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
     195,  -737,   644,  -737,     7,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,   647,   519,   650,    68,  -737,  -737,   569,  -737,
     651,  -737,   576,  -737,  -737,   648,  -737,  -737,   150,  -737,
     145,   648,  -737,  -737,   654,   657,   658,   339,  -737,  -737,
    -737,  -737,  -737,  -737,   660,   548,   529,   541,   145,  -737,
     589,  -737,  -737,  -737,  -737,  -737
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   115,     9,   237,    11,   390,    13,
     414,    15,   315,    17,   323,    19,   360,    21,   202,    23,
     500,    25,   557,    27,    45,    39,     0,     0,     0,     0,
       0,   416,     0,   325,   362,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   555,   549,   551,   553,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   104,     0,
       0,   435,   437,   439,   128,   130,     0,     0,     0,     0,
     229,   313,   352,   286,   402,   404,   180,   461,   194,   213,
       0,   485,   498,    97,     0,    70,    72,    73,    74,    75,
      90,    91,    78,    79,    80,    81,    85,    86,    76,    77,
      83,    84,    95,    96,    92,    93,    94,    82,    87,    88,
      89,   117,   119,   123,     0,   114,     0,   106,   108,   109,
     110,   111,   112,   113,   267,   269,   271,   382,   265,   273,
     275,     0,     0,   279,   277,   406,   457,   264,   241,   242,
     243,   255,     0,   239,   246,   259,   260,   261,   247,   248,
     251,   253,   249,   250,   244,   245,   262,   263,   252,   256,
     257,   258,   254,   400,   399,   396,   395,     0,   392,   394,
     397,   398,   455,   443,   445,   449,   447,   453,   451,   441,
     434,   428,   432,   433,     0,   417,   418,   429,   430,   431,
     425,   420,   426,   422,   423,   424,   427,   421,     0,   342,
     165,     0,   346,   344,   349,     0,   338,   339,     0,   326,
     327,   329,   341,   330,   331,   332,   348,   333,   334,   335,
     336,   337,   376,     0,     0,   374,   375,   378,   379,     0,
     363,   364,   366,   367,   368,   369,   370,   371,   372,   373,
     209,   211,   206,     0,   204,   207,   208,     0,   522,   524,
       0,   527,     0,     0,   531,   535,     0,     0,     0,   540,
     547,   520,   518,   519,     0,   502,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     562,     0,   559,   561,    44,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    55,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   238,     0,     0,   391,     0,     0,
       0,     0,     0,     0,     0,     0,   415,     0,   316,     0,
       0,     0,     0,     0,     0,     0,   324,     0,     0,     0,
       0,   361,     0,     0,     0,     0,   203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   501,     0,     0,   558,    48,    41,     0,     0,
       0,     0,     0,     0,    59,     0,   102,   103,     0,     0,
       0,     0,     0,    98,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   484,     0,     0,
      71,     0,     0,     0,   127,   107,     0,     0,     0,     0,
       0,     0,     0,   284,   285,     0,     0,     0,     0,   240,
       0,   393,     0,     0,     0,     0,     0,     0,     0,     0,
     419,     0,     0,   340,     0,     0,     0,   351,   328,     0,
     380,   381,   365,     0,     0,   205,   521,     0,     0,   526,
       0,   529,   530,     0,     0,   537,   538,   539,     0,     0,
     503,     0,   560,     0,     0,     0,   550,   552,   554,     0,
     436,   438,   440,     0,     0,   231,   317,   354,   288,    38,
     403,   405,     0,     0,   196,     0,     0,     0,    49,   118,
     121,   122,   120,   125,   126,   124,   268,   270,   272,   384,
     266,   274,   276,   281,   282,   283,   280,   278,   408,     0,
     401,   456,   444,   446,   450,   448,   454,   452,   442,   343,
     166,   347,   345,   350,   377,   210,   212,   523,   525,   528,
     533,   534,   532,   536,   542,   543,   544,   545,   546,   541,
     548,     0,    42,     0,     0,     0,   152,   158,   160,   162,
       0,     0,     0,     0,     0,   174,   176,     0,     0,     0,
       0,     0,   151,     0,   132,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   147,   148,   149,   144,   150,
     145,   146,     0,   235,     0,   232,   233,   321,     0,   318,
     319,   358,     0,   355,   356,   292,     0,   289,   290,   189,
     190,   191,   192,   193,     0,   182,   184,   185,   186,   187,
     188,   465,     0,   463,   200,     0,   197,   198,     0,     0,
       0,     0,     0,     0,     0,   215,   217,   218,   219,   220,
     221,   222,   494,   496,   493,   491,   492,     0,   487,   489,
     490,     0,    51,   388,     0,   385,   386,   412,     0,   409,
     410,   459,     0,   566,     0,   564,    67,   556,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   131,     0,   230,
       0,   325,   314,     0,   362,   353,     0,     0,   287,     0,
       0,   181,   467,     0,   462,     0,   195,     0,     0,     0,
       0,     0,     0,     0,     0,   214,     0,     0,     0,   486,
     499,    53,     0,    52,     0,   383,     0,   416,   407,     0,
       0,   458,     0,     0,   563,     0,     0,     0,     0,   164,
     167,   168,   169,   170,     0,     0,   178,   179,   171,   172,
     173,   133,     0,   234,     0,   320,     0,   357,   312,   309,
     299,   300,   302,   296,   297,   298,   308,   307,     0,   294,
     301,   310,   311,   303,   304,   305,   306,   291,   183,   482,
     480,   481,   473,   474,   478,   479,   475,   476,   477,     0,
     468,   469,   471,   472,   464,     0,   199,   223,   224,   225,
     226,   227,   228,   216,     0,     0,   488,    50,     0,     0,
     387,     0,   411,     0,   580,     0,   578,   576,   570,   574,
     575,     0,   568,   572,   573,   571,   565,   154,   155,   156,
     157,   153,   159,   161,   163,   175,   177,   236,   322,   359,
       0,   293,     0,   466,     0,   201,   495,   497,    54,   389,
     413,   460,     0,     0,     0,     0,   567,   295,     0,   470,
       0,   577,     0,   569,   483,     0,   579,   584,     0,   582,
       0,     0,   581,   592,     0,     0,     0,     0,   586,   588,
     589,   590,   591,   583,     0,     0,     0,     0,     0,   585,
       0,   594,   595,   596,   587,   593
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,   -51,  -737,   204,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,    58,  -737,  -737,  -737,
     -66,  -737,  -737,  -737,   333,  -737,  -737,  -737,  -737,   142,
     313,   -23,   -21,     0,  -737,  -737,     6,  -737,  -737,   128,
     309,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   134,   -65,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   -73,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   -70,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   -74,  -737,  -737,  -737,
     -67,   295,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   -39,
    -737,  -737,  -737,  -737,  -737,  -737,  -736,  -737,  -737,  -737,
      -7,  -737,  -737,  -737,    -9,   381,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -730,  -737,  -737,  -737,   -25,  -737,
    -724,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   -10,
    -737,  -737,  -148,   -61,  -737,  -737,  -737,  -737,  -737,     2,
    -737,  -737,  -737,     9,  -737,   355,  -737,   -68,  -737,  -737,
    -737,  -737,  -737,   -62,  -737,  -737,  -737,  -737,  -737,   -17,
    -737,  -737,  -737,    10,  -737,  -737,  -737,    11,  -737,   356,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,   -15,  -737,  -737,  -737,   -12,   387,  -737,  -737,   -54,
    -737,   -34,  -737,  -737,  -737,  -737,  -737,   -20,  -737,  -737,
    -737,   -13,  -737,   378,   -46,  -737,   -11,  -737,    -1,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -719,  -737,  -737,  -737,
    -737,  -737,  -737,    14,  -737,  -737,  -737,  -126,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,     1,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,   223,   350,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   247,
     349,  -737,  -737,  -737,    -8,  -737,  -737,  -131,  -737,  -737,
    -737,  -737,  -737,  -737,  -144,  -737,  -737,  -160,  -737,  -737,
    -737,  -737,  -737
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   550,
      82,    83,    39,    64,    79,    80,   559,   712,   782,   783,
     123,    41,    66,    91,    92,    93,   329,    43,    67,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   337,   156,
     157,    45,    68,   158,   364,   159,   365,   562,   160,   366,
     565,   161,   133,   343,   134,   344,   633,   634,   635,   729,
     891,   636,   730,   637,   731,   638,   732,   639,   247,   400,
     641,   642,   643,   644,   645,   646,   647,   648,   738,   649,
     739,   650,   651,   135,   355,   674,   675,   676,   677,   678,
     679,   680,   136,   357,   685,   686,   687,   765,    59,    75,
     283,   284,   285,   413,   286,   414,   137,   358,   694,   695,
     696,   697,   698,   699,   700,   701,   138,   349,   654,   655,
     656,   748,    47,    69,   182,   183,   184,   374,   185,   370,
     186,   371,   187,   372,   188,   375,   189,   376,   190,   380,
     191,   379,   576,   192,   193,   139,   352,   666,   667,   668,
     757,   828,   829,   140,   350,    53,    72,   658,   659,   660,
     751,    55,    73,   248,   249,   250,   251,   252,   253,   254,
     399,   255,   403,   256,   402,   257,   258,   404,   259,   141,
     351,   662,   663,   664,   754,    57,    74,   269,   270,   271,
     272,   273,   408,   274,   275,   276,   277,   195,   373,   714,
     715,   716,   784,    49,    70,   207,   208,   209,   385,   142,
     353,   143,   354,   198,   381,   718,   719,   720,   787,    51,
      71,   224,   225,   226,   144,   340,   145,   341,   146,   342,
     230,   395,   231,   389,   232,   390,   233,   392,   234,   391,
     235,   394,   236,   393,   237,   388,   202,   382,   722,   790,
     147,   356,   682,   683,   762,   849,   850,   851,   852,   853,
     902,   148,   149,   360,   707,   708,   709,   776,   710,   777,
     150,   361,    61,    76,   304,   305,   306,   307,   418,   308,
     419,   309,   310,   421,   311,   312,   313,   424,   602,   314,
     425,   315,   316,   317,   318,   429,   609,   319,   430,    94,
     331,    95,   332,    96,   333,    97,   330,    63,    77,   321,
     322,   323,   433,   724,   725,   792,   881,   882,   883,   884,
     914,   885,   912,   928,   929,   930,   937,   938,   939,   944,
     940,   941,   942
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   266,   155,   177,   204,   220,   267,   246,   265,   282,
     301,   238,   268,    78,   162,   196,   210,   222,    84,   260,
     278,   824,   302,   199,    29,   227,    30,   825,    31,   101,
     102,   103,   600,   827,   163,   197,   211,   223,   836,   261,
     279,    28,   303,   151,   152,   205,   178,   153,   179,    40,
     154,   335,   194,   206,   221,    81,   336,    42,   200,    44,
     228,   239,   111,   112,   240,   280,   281,   362,   201,   180,
     229,   111,   363,    98,   368,   181,   114,   115,   760,   369,
      46,   761,    99,   100,   101,   102,   103,   104,   105,   839,
     383,   240,    48,   241,   242,   384,    50,   243,   244,   245,
     114,   115,   112,   114,   115,   887,   888,   889,   890,   106,
     107,   108,   109,   110,   203,   114,   115,   111,   112,   604,
     605,   606,   607,   763,    89,   240,   764,   320,   113,   174,
     386,   114,   115,   280,   281,   387,    85,   114,   115,   601,
      52,   793,   116,   117,   794,    86,    87,    88,    54,   114,
     115,   608,   415,   931,   431,   118,   932,   416,   119,   432,
      89,    89,   434,   362,   824,   120,   121,   435,   726,   122,
     825,    56,    32,    33,    34,    35,   827,   100,   101,   102,
     103,   836,    58,   434,    89,   702,   703,    89,   727,   368,
     101,   102,   103,   324,   728,   560,   561,   745,   874,    89,
     875,   876,   746,   106,   107,   108,   745,    60,   164,   165,
     166,   747,   112,   563,   564,    89,   100,   101,   102,   103,
      62,    89,   325,   167,   112,   114,   115,   168,   169,   170,
     171,   172,   173,    89,   326,   327,   774,   114,   115,   174,
     175,   775,   106,   107,   108,   778,   110,   176,   328,   212,
     779,   112,   240,   213,   214,   215,   216,   217,   218,   396,
     219,   431,   397,   383,   114,   115,   780,   169,   897,    90,
     334,   173,   338,   398,   436,   437,   933,   339,   174,   934,
     935,   936,   616,   573,   574,   575,   176,   617,   618,   619,
     620,   621,   622,   623,   624,   625,   626,   627,   628,   629,
     630,   631,   155,   240,   262,   241,   242,   263,   264,    89,
     345,   346,   240,   900,   162,   114,   115,   177,   901,   347,
     204,    89,   688,   689,   690,   691,   692,   693,   415,   196,
     386,   220,   210,   905,   163,   909,   348,   199,   359,   266,
     915,   246,   948,   222,   267,   916,   265,   949,    89,   197,
     268,   227,   211,   260,   669,   670,   671,   672,   278,   673,
     178,   205,   179,   223,   367,   301,   194,   377,   378,   206,
     114,   115,   200,   261,   401,   405,   406,   302,   279,   407,
     221,   409,   201,   180,   410,   412,   228,   411,   417,   181,
     536,   537,   538,   420,   422,   423,   229,   303,   426,    89,
     427,   428,   438,   439,   440,   441,   442,   443,    89,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,    89,   463,   464,   465,   466,   467,
     468,   469,   471,   596,   472,   473,   476,   474,   477,   478,
     640,   640,   479,   155,   480,   481,   482,   632,   632,   484,
     483,   485,   612,   486,   487,   162,   488,   490,   492,   493,
     704,   301,   494,   495,   496,   497,   498,   499,   501,   502,
     503,   504,   705,   302,   505,   163,   506,   507,   509,   510,
     511,   513,   514,   516,   517,   518,   519,   520,   523,   521,
     522,   524,   706,   303,   528,   525,   529,   531,   526,   527,
     533,   534,   535,   603,   539,   543,   540,   544,   541,   542,
     545,   546,   547,   548,   733,   551,    30,   552,   553,   554,
     581,   566,   555,   556,   557,   558,   569,   567,   568,   570,
     571,   572,   577,   578,   579,   580,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     597,   598,   599,   610,   611,   653,   781,   657,   661,   665,
     681,   684,   713,   717,   723,   721,   734,   735,   736,   737,
     740,   741,   742,   743,   744,   750,   800,   749,   753,   752,
     755,   756,   758,   759,   767,   766,   768,   769,   770,   771,
     772,   773,   786,   799,   785,   789,   788,   795,   796,   791,
     797,   798,   801,   804,   805,   864,   865,   802,   868,   867,
     803,   806,   873,   904,   898,   899,   913,   903,   918,   910,
     807,   920,   808,   809,   922,   927,   925,   810,   945,   857,
     858,   946,   947,   859,   950,   549,   860,   615,   444,   861,
     862,   892,   640,   921,   893,   470,   613,   475,   652,   632,
     811,   266,   177,   952,   823,   246,   267,   894,   265,   841,
     838,   818,   268,   856,   196,   953,   840,   260,   855,   282,
     278,   842,   199,   831,   951,   895,   896,   906,   844,   907,
     515,   833,   704,   908,   197,   911,   846,   261,   204,   878,
     279,   220,   924,   832,   705,   178,   877,   179,   845,   926,
     210,   194,   826,   222,   819,   863,   820,   200,   879,   812,
     830,   227,   955,   813,   706,   843,   834,   201,   180,   837,
     211,   847,   917,   223,   181,   815,   835,   821,   880,   205,
     814,   848,   508,   822,   489,   816,   817,   206,   512,   872,
     221,   870,   869,   491,   871,   500,   228,   854,   919,   866,
     711,   530,   614,   532,   923,   886,   229,   943,   954,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   823,     0,     0,
       0,   841,     0,     0,   818,     0,     0,     0,   840,     0,
       0,     0,   878,   842,     0,     0,   831,     0,     0,   877,
     844,     0,     0,     0,   833,     0,     0,     0,   846,     0,
       0,   879,     0,     0,     0,     0,   832,     0,     0,     0,
     845,     0,     0,     0,     0,   826,     0,   819,     0,   820,
       0,   880,     0,   830,     0,     0,     0,   843,     0,   834,
       0,     0,     0,   847,     0,     0,     0,     0,     0,   835,
     821,     0,     0,   848,     0,     0,   822
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    74,    68,    69,    70,    71,    74,    73,    74,    75,
      76,    72,    74,    64,    68,    69,    70,    71,    10,    73,
      74,   757,    76,    69,     5,    71,     7,   757,     9,    22,
      23,    24,    15,   757,    68,    69,    70,    71,   757,    73,
      74,     0,    76,    12,    13,    70,    69,    16,    69,     7,
      19,     3,    69,    70,    71,   153,     8,     7,    69,     7,
      71,    27,    55,    56,    57,    94,    95,     3,    69,    69,
      71,    55,     8,    11,     3,    69,    69,    70,     3,     8,
       7,     6,    20,    21,    22,    23,    24,    25,    26,    82,
       3,    57,     7,    59,    60,     8,     7,    63,    64,    65,
      69,    70,    56,    69,    70,    28,    29,    30,    31,    47,
      48,    49,    50,    51,    68,    69,    70,    55,    56,   124,
     125,   126,   127,     3,   153,    57,     6,   129,    66,    83,
       3,    69,    70,    94,    95,     8,   128,    69,    70,   122,
       7,     3,    80,    81,     6,   137,   138,   139,     7,    69,
      70,   156,     3,     3,     3,    93,     6,     8,    96,     8,
     153,   153,     3,     3,   900,   103,   104,     8,     8,   107,
     900,     7,   153,   154,   155,   156,   900,    21,    22,    23,
      24,   900,     7,     3,   153,   105,   106,   153,     8,     3,
      22,    23,    24,     6,     8,    14,    15,     3,   130,   153,
     132,   133,     8,    47,    48,    49,     3,     7,    52,    53,
      54,     8,    56,    17,    18,   153,    21,    22,    23,    24,
       7,   153,     3,    67,    56,    69,    70,    71,    72,    73,
      74,    75,    76,   153,     4,     8,     3,    69,    70,    83,
      84,     8,    47,    48,    49,     3,    51,    91,     3,    81,
       8,    56,    57,    85,    86,    87,    88,    89,    90,     8,
      92,     3,     3,     3,    69,    70,     8,    72,     8,   335,
       4,    76,     4,     8,   325,   326,   131,     4,    83,   134,
     135,   136,    27,    77,    78,    79,    91,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,   368,    57,    58,    59,    60,    61,    62,   153,
       4,     4,    57,     3,   368,    69,    70,   383,     8,     4,
     386,   153,    97,    98,    99,   100,   101,   102,     3,   383,
       3,   397,   386,     8,   368,     8,     4,   383,     4,   412,
       3,   407,     3,   397,   412,     8,   412,     8,   153,   383,
     412,   397,   386,   407,    85,    86,    87,    88,   412,    90,
     383,   386,   383,   397,     4,   431,   383,     4,     4,   386,
      69,    70,   383,   407,     4,     4,     8,   431,   412,     3,
     397,     4,   383,   383,     4,     3,   397,     8,     4,   383,
     441,   442,   443,     4,     4,     4,   397,   431,     4,   153,
       4,     4,   153,     4,     4,     4,     4,     4,   153,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,     4,   156,   156,     4,
       4,     4,     4,     4,   154,   154,   154,   154,     4,     4,
       4,     4,     4,     4,   153,     4,     4,     4,     4,   154,
       4,     4,     4,   514,     4,     4,     4,   156,     4,     4,
     543,   544,     4,   539,     4,     4,     4,   543,   544,   156,
     154,     4,   533,     4,     4,   539,     4,     4,     4,     4,
     556,   557,     4,     4,     4,     4,     4,     4,     4,     4,
     154,     4,   556,   557,     4,   539,     4,   156,     4,   156,
     156,     4,     4,   156,     4,     4,   154,     4,     4,   154,
     154,     4,   556,   557,     4,   156,     4,     4,   156,   156,
       4,     7,     7,   123,     7,     7,   153,     7,   153,   153,
       5,     5,     5,     5,     4,   153,     7,     5,     5,     5,
     492,   153,     7,     7,     7,     5,     5,   153,   153,   153,
     153,   153,   153,     5,     7,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,     5,     7,   153,     7,     7,     7,
       7,     7,     7,     7,     7,    92,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   156,     6,     3,     6,
       6,     3,     6,     3,     3,     6,     4,     4,     4,     4,
       4,     4,     3,   154,     6,     3,     6,     4,     4,     8,
       4,     4,   154,     4,     4,     4,     4,   156,     3,     6,
     154,   154,     4,     3,     8,     8,     4,     8,     4,     8,
     154,     4,   154,   154,     4,     7,     5,   156,     4,   154,
     154,     4,     4,   154,     4,   461,   154,   539,   335,   154,
     154,   153,   745,   154,   153,   362,   534,   368,   544,   745,
     745,   754,   748,   154,   757,   751,   754,   153,   754,   762,
     760,   757,   754,   767,   748,   154,   762,   751,   765,   765,
     754,   762,   748,   757,   156,   153,   153,   153,   762,   153,
     415,   757,   778,   153,   748,   153,   762,   751,   784,   792,
     754,   787,   153,   757,   778,   748,   792,   748,   762,   153,
     784,   748,   757,   787,   757,   774,   757,   748,   792,   748,
     757,   787,   153,   750,   778,   762,   757,   748,   748,   759,
     784,   762,   900,   787,   748,   753,   757,   757,   792,   784,
     751,   762,   407,   757,   383,   754,   756,   784,   412,   789,
     787,   786,   784,   386,   787,   397,   787,   763,   904,   778,
     557,   431,   535,   434,   915,   793,   787,   931,   948,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   900,    -1,    -1,
      -1,   904,    -1,    -1,   900,    -1,    -1,    -1,   904,    -1,
      -1,    -1,   915,   904,    -1,    -1,   900,    -1,    -1,   915,
     904,    -1,    -1,    -1,   900,    -1,    -1,    -1,   904,    -1,
      -1,   915,    -1,    -1,    -1,    -1,   900,    -1,    -1,    -1,
     904,    -1,    -1,    -1,    -1,   900,    -1,   900,    -1,   900,
      -1,   915,    -1,   900,    -1,    -1,    -1,   904,    -1,   900,
      -1,    -1,    -1,   904,    -1,    -1,    -1,    -1,    -1,   900,
     900,    -1,    -1,   904,    -1,    -1,   900
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,     0,     5,
       7,     9,   153,   154,   155,   156,   172,   173,   174,   179,
       7,   188,     7,   194,     7,   208,     7,   289,     7,   370,
       7,   386,     7,   322,     7,   328,     7,   352,     7,   265,
       7,   439,     7,   474,   180,   175,   189,   195,   209,   290,
     371,   387,   323,   329,   353,   266,   440,   475,   172,   181,
     182,   153,   177,   178,    10,   128,   137,   138,   139,   153,
     187,   190,   191,   192,   466,   468,   470,   472,    11,    20,
      21,    22,    23,    24,    25,    26,    47,    48,    49,    50,
      51,    55,    56,    66,    69,    70,    80,    81,    93,    96,
     103,   104,   107,   187,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   219,   221,   250,   259,   273,   283,   312,
     320,   346,   376,   378,   391,   393,   395,   417,   428,   429,
     437,    12,    13,    16,    19,   187,   206,   207,   210,   212,
     215,   218,   376,   378,    52,    53,    54,    67,    71,    72,
      73,    74,    75,    76,    83,    84,    91,   187,   198,   199,
     200,   203,   291,   292,   293,   295,   297,   299,   301,   303,
     305,   307,   310,   311,   346,   364,   376,   378,   380,   391,
     393,   395,   413,    68,   187,   305,   346,   372,   373,   374,
     376,   378,    81,    85,    86,    87,    88,    89,    90,    92,
     187,   346,   376,   378,   388,   389,   390,   391,   393,   395,
     397,   399,   401,   403,   405,   407,   409,   411,   320,    27,
      57,    59,    60,    63,    64,    65,   187,   235,   330,   331,
     332,   333,   334,   335,   336,   338,   340,   342,   343,   345,
     376,   378,    58,    61,    62,   187,   235,   334,   340,   354,
     355,   356,   357,   358,   360,   361,   362,   363,   376,   378,
      94,    95,   187,   267,   268,   269,   271,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   187,   376,   378,   441,   442,   443,   444,   446,   448,
     449,   451,   452,   453,   456,   458,   459,   460,   461,   464,
     129,   476,   477,   478,     6,     3,     4,     8,     3,   193,
     473,   467,   469,   471,     4,     3,     8,   205,     4,     4,
     392,   394,   396,   220,   222,     4,     4,     4,     4,   284,
     321,   347,   313,   377,   379,   251,   418,   260,   274,     4,
     430,   438,     3,     8,   211,   213,   216,     4,     3,     8,
     296,   298,   300,   365,   294,   302,   304,     4,     4,   308,
     306,   381,   414,     3,     8,   375,     3,     8,   412,   400,
     402,   406,   404,   410,   408,   398,     8,     3,     8,   337,
     236,     4,   341,   339,   344,     4,     8,     3,   359,     4,
       4,     8,     3,   270,   272,     3,     8,     4,   445,   447,
       4,   450,     4,     4,   454,   457,     4,     4,     4,   462,
     465,     3,     8,   479,     3,     8,   172,   172,   153,     4,
       4,     4,     4,     4,   191,     4,   156,   156,     4,     4,
       4,     4,     4,   154,   154,   154,   154,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   154,     4,     4,
     197,     4,     4,     4,   156,   207,     4,     4,     4,     4,
       4,     4,     4,   154,   156,     4,     4,     4,     4,   292,
       4,   373,     4,     4,     4,     4,     4,     4,     4,     4,
     390,     4,     4,   154,     4,     4,     4,   156,   332,     4,
     156,   156,   356,     4,     4,   268,   156,     4,     4,   154,
       4,   154,   154,     4,     4,   156,   156,   156,     4,     4,
     442,     4,   477,     4,     7,     7,   172,   172,   172,     7,
     153,   153,   153,     7,     7,     5,     5,     5,     5,   174,
     176,   153,     5,     5,     5,     7,     7,     7,     5,   183,
      14,    15,   214,    17,    18,   217,   153,   153,   153,     5,
     153,   153,   153,    77,    78,    79,   309,   153,     5,     7,
     153,   183,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   172,   153,   153,   153,
      15,   122,   455,   123,   124,   125,   126,   127,   156,   463,
     153,     5,   172,   196,   476,   206,    27,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,   187,   223,   224,   225,   228,   230,   232,   234,
     235,   237,   238,   239,   240,   241,   242,   243,   244,   246,
     248,   249,   223,     7,   285,   286,   287,     7,   324,   325,
     326,     7,   348,   349,   350,     7,   314,   315,   316,    85,
      86,    87,    88,    90,   252,   253,   254,   255,   256,   257,
     258,     7,   419,   420,     7,   261,   262,   263,    97,    98,
      99,   100,   101,   102,   275,   276,   277,   278,   279,   280,
     281,   282,   105,   106,   187,   376,   378,   431,   432,   433,
     435,   441,   184,     7,   366,   367,   368,     7,   382,   383,
     384,    92,   415,     7,   480,   481,     8,     8,     8,   226,
     229,   231,   233,     4,     4,     4,     4,     4,   245,   247,
       4,     4,     4,     4,     4,     3,     8,     8,   288,     6,
       3,   327,     6,     3,   351,     6,     3,   317,     6,     3,
       3,     6,   421,     3,     6,   264,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   434,   436,     3,     8,
       8,   153,   185,   186,   369,     6,     3,   385,     6,     3,
     416,     8,   482,     3,     6,     4,     4,     4,     4,   154,
     156,   154,   156,   154,     4,     4,   154,   154,   154,   154,
     156,   224,   291,   287,   330,   326,   354,   350,   187,   198,
     199,   200,   203,   235,   283,   301,   305,   307,   318,   319,
     346,   376,   378,   391,   393,   395,   413,   316,   253,    82,
     187,   235,   320,   346,   376,   378,   391,   393,   395,   422,
     423,   424,   425,   426,   420,   267,   263,   154,   154,   154,
     154,   154,   154,   276,     4,     4,   432,     6,     3,   372,
     368,   388,   384,     4,   130,   132,   133,   187,   235,   376,
     378,   483,   484,   485,   486,   488,   481,    28,    29,    30,
      31,   227,   153,   153,   153,   153,   153,     8,     8,     8,
       3,     8,   427,     8,     3,     8,   153,   153,   153,     8,
       8,   153,   489,     4,   487,     3,     8,   319,     4,   424,
       4,   154,     4,   484,   153,     5,   153,     7,   490,   491,
     492,     3,     6,   131,   134,   135,   136,   493,   494,   495,
     497,   498,   499,   491,   496,     4,     4,     4,     3,     8,
       4,   156,   154,   154,   494,   153
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
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
     197,   197,   197,   197,   197,   197,   197,   197,   198,   199,
     200,   201,   202,   203,   205,   204,   206,   206,   207,   207,
     207,   207,   207,   207,   207,   209,   208,   211,   210,   213,
     212,   214,   214,   216,   215,   217,   217,   218,   220,   219,
     222,   221,   223,   223,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   226,   225,   227,   227,   227,   227,   229,   228,
     231,   230,   233,   232,   234,   236,   235,   237,   238,   239,
     240,   241,   242,   243,   245,   244,   247,   246,   248,   249,
     251,   250,   252,   252,   253,   253,   253,   253,   253,   254,
     255,   256,   257,   258,   260,   259,   261,   261,   262,   262,
     264,   263,   266,   265,   267,   267,   267,   268,   268,   270,
     269,   272,   271,   274,   273,   275,   275,   276,   276,   276,
     276,   276,   276,   277,   278,   279,   280,   281,   282,   284,
     283,   285,   285,   286,   286,   288,   287,   290,   289,   291,
     291,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   294,   293,   296,   295,   298,
     297,   300,   299,   302,   301,   304,   303,   306,   305,   308,
     307,   309,   309,   309,   310,   311,   313,   312,   314,   314,
     315,   315,   317,   316,   318,   318,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   321,   320,   323,   322,   324,   324,   325,
     325,   327,   326,   329,   328,   330,   330,   331,   331,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   333,
     334,   335,   337,   336,   339,   338,   341,   340,   342,   344,
     343,   345,   347,   346,   348,   348,   349,   349,   351,   350,
     353,   352,   354,   354,   355,   355,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   357,   359,   358,   360,   361,
     362,   363,   365,   364,   366,   366,   367,   367,   369,   368,
     371,   370,   372,   372,   373,   373,   373,   373,   373,   373,
     375,   374,   377,   376,   379,   378,   381,   380,   382,   382,
     383,   383,   385,   384,   387,   386,   388,   388,   389,   389,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   392,   391,   394,   393,   396,
     395,   398,   397,   400,   399,   402,   401,   404,   403,   406,
     405,   408,   407,   410,   409,   412,   411,   414,   413,   416,
     415,   418,   417,   419,   419,   421,   420,   422,   422,   423,
     423,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   425,   427,   426,   428,   430,   429,   431,   431,   432,
     432,   432,   432,   432,   434,   433,   436,   435,   438,   437,
     440,   439,   441,   441,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   443,   445,   444,   447,   446,   448,   450,   449,   451,
     452,   454,   453,   455,   455,   457,   456,   458,   459,   460,
     462,   461,   463,   463,   463,   463,   463,   465,   464,   467,
     466,   469,   468,   471,   470,   473,   472,   475,   474,   476,
     476,   477,   479,   478,   480,   480,   482,   481,   483,   483,
     484,   484,   484,   484,   484,   484,   484,   485,   487,   486,
     489,   488,   490,   490,   492,   491,   493,   493,   494,   494,
     494,   494,   496,   495,   497,   498,   499
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     3,     3,     3
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
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"keyspace\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
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
  "database_map_params", "database_map_param", "database_type", "$@27",
  "db_type", "user", "$@28", "password", "$@29", "host", "$@30", "port",
  "name", "$@31", "persist", "lfc_interval", "readonly", "connect_timeout",
  "request_timeout", "tcp_keepalive", "tcp_nodelay", "contact_points",
  "$@32", "keyspace", "$@33", "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@34",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@35", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@36",
  "sub_hooks_library", "$@37", "hooks_params", "hooks_param", "library",
  "$@38", "parameters", "$@39", "expired_leases_processing", "$@40",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@41",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@42",
  "sub_subnet4", "$@43", "subnet4_params", "subnet4_param", "subnet",
  "$@44", "subnet_4o6_interface", "$@45", "subnet_4o6_interface_id",
  "$@46", "subnet_4o6_subnet", "$@47", "interface", "$@48", "interface_id",
  "$@49", "client_class", "$@50", "reservation_mode", "$@51", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@52",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@53", "shared_network_params", "shared_network_param",
  "option_def_list", "$@54", "sub_option_def_list", "$@55",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@56", "sub_option_def", "$@57",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@58",
  "option_def_record_types", "$@59", "space", "$@60", "option_def_space",
  "option_def_encapsulate", "$@61", "option_def_array", "option_data_list",
  "$@62", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@63", "sub_option_data", "$@64",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@65",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@66", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@67", "sub_pool4", "$@68",
  "pool_params", "pool_param", "pool_entry", "$@69", "user_context",
  "$@70", "comment", "$@71", "reservations", "$@72", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@73", "sub_reservation",
  "$@74", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@75", "server_hostname", "$@76",
  "boot_file_name", "$@77", "ip_address", "$@78", "duid", "$@79",
  "hw_address", "$@80", "client_id_value", "$@81", "circuit_id_value",
  "$@82", "flex_id_value", "$@83", "hostname", "$@84",
  "reservation_client_classes", "$@85", "relay", "$@86", "relay_map",
  "$@87", "client_classes", "$@88", "client_classes_list",
  "client_class_entry", "$@89", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@90", "dhcp4o6_port",
  "control_socket", "$@91", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@92",
  "control_socket_name", "$@93", "dhcp_ddns", "$@94", "sub_dhcp_ddns",
  "$@95", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@96", "server_ip", "$@97", "server_port",
  "sender_ip", "$@98", "sender_port", "max_queue_size", "ncr_protocol",
  "$@99", "ncr_protocol_value", "ncr_format", "$@100",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@101", "replace_client_name_value",
  "generated_prefix", "$@102", "dhcp6_json_object", "$@103",
  "dhcpddns_json_object", "$@104", "control_agent_json_object", "$@105",
  "logging_object", "$@106", "sub_logging", "$@107", "logging_params",
  "logging_param", "loggers", "$@108", "loggers_entries", "logger_entry",
  "$@109", "logger_params", "logger_param", "debuglevel", "severity",
  "$@110", "output_options_list", "$@111", "output_options_list_content",
  "output_entry", "$@112", "output_params_list", "output_params", "output",
  "$@113", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   240,   240,   240,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   245,   246,   246,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   251,   252,   252,   260,   261,
     262,   263,   264,   265,   266,   269,   274,   274,   285,   288,
     289,   292,   296,   303,   303,   310,   311,   314,   318,   325,
     325,   332,   333,   336,   340,   351,   361,   361,   377,   378,
     382,   383,   384,   385,   386,   387,   390,   390,   405,   405,
     414,   415,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   448,   453,
     458,   463,   468,   473,   479,   479,   490,   491,   494,   495,
     496,   497,   498,   499,   500,   503,   503,   512,   512,   522,
     522,   529,   530,   533,   533,   540,   542,   546,   552,   552,
     564,   564,   576,   577,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   600,   600,   607,   608,   609,   610,   613,   613,
     621,   621,   629,   629,   637,   642,   642,   650,   655,   660,
     665,   670,   675,   680,   685,   685,   693,   693,   701,   706,
     711,   711,   721,   722,   725,   726,   727,   728,   729,   732,
     737,   742,   747,   752,   757,   757,   767,   768,   771,   772,
     775,   775,   785,   785,   795,   796,   797,   800,   801,   804,
     804,   812,   812,   820,   820,   831,   832,   835,   836,   837,
     838,   839,   840,   843,   848,   853,   858,   863,   868,   876,
     876,   889,   890,   893,   894,   901,   901,   927,   927,   938,
     939,   943,   944,   945,   946,   947,   948,   949,   950,   951,
     952,   953,   954,   955,   956,   957,   958,   959,   960,   961,
     962,   963,   964,   965,   966,   969,   969,   977,   977,   985,
     985,   993,   993,  1001,  1001,  1009,  1009,  1017,  1017,  1025,
    1025,  1032,  1033,  1034,  1037,  1042,  1049,  1049,  1060,  1061,
    1065,  1066,  1069,  1069,  1077,  1078,  1081,  1082,  1083,  1084,
    1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,  1093,  1094,
    1095,  1096,  1097,  1104,  1104,  1117,  1117,  1126,  1127,  1130,
    1131,  1136,  1136,  1151,  1151,  1165,  1166,  1169,  1170,  1173,
    1174,  1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,  1185,
    1187,  1192,  1194,  1194,  1202,  1202,  1210,  1210,  1218,  1220,
    1220,  1228,  1237,  1237,  1249,  1250,  1255,  1256,  1261,  1261,
    1273,  1273,  1285,  1286,  1291,  1292,  1297,  1298,  1299,  1300,
    1301,  1302,  1303,  1304,  1305,  1308,  1310,  1310,  1318,  1320,
    1322,  1327,  1335,  1335,  1347,  1348,  1351,  1352,  1355,  1355,
    1365,  1365,  1375,  1376,  1379,  1380,  1381,  1382,  1383,  1384,
    1387,  1387,  1395,  1395,  1420,  1420,  1450,  1450,  1460,  1461,
    1464,  1465,  1468,  1468,  1477,  1477,  1486,  1487,  1490,  1491,
    1495,  1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,  1504,
    1505,  1506,  1507,  1508,  1509,  1512,  1512,  1520,  1520,  1528,
    1528,  1536,  1536,  1544,  1544,  1552,  1552,  1560,  1560,  1568,
    1568,  1576,  1576,  1584,  1584,  1592,  1592,  1605,  1605,  1615,
    1615,  1626,  1626,  1636,  1637,  1640,  1640,  1650,  1651,  1654,
    1655,  1658,  1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,
    1667,  1670,  1672,  1672,  1684,  1691,  1691,  1701,  1702,  1705,
    1706,  1707,  1708,  1709,  1712,  1712,  1720,  1720,  1730,  1730,
    1742,  1742,  1752,  1753,  1756,  1757,  1758,  1759,  1760,  1761,
    1762,  1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,  1771,
    1772,  1775,  1780,  1780,  1788,  1788,  1796,  1801,  1801,  1809,
    1814,  1819,  1819,  1827,  1828,  1831,  1831,  1839,  1844,  1849,
    1854,  1854,  1862,  1865,  1868,  1871,  1874,  1880,  1880,  1890,
    1890,  1897,  1897,  1904,  1904,  1916,  1916,  1926,  1926,  1937,
    1938,  1942,  1946,  1946,  1958,  1959,  1963,  1963,  1971,  1972,
    1975,  1976,  1977,  1978,  1979,  1980,  1981,  1984,  1989,  1989,
    1997,  1997,  2007,  2008,  2011,  2011,  2019,  2020,  2023,  2024,
    2025,  2026,  2029,  2029,  2037,  2042,  2047
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
#line 4556 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2052 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
