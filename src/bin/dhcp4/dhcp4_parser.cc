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
      case 171: // value
      case 175: // map_value
      case 213: // socket_type
      case 216: // outbound_interface_value
      case 226: // db_type
      case 307: // hr_mode
      case 453: // ncr_protocol_value
      case 461: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 155: // "boolean"
        value.move< bool > (that.value);
        break;

      case 154: // "floating point"
        value.move< double > (that.value);
        break;

      case 153: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 152: // "constant string"
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
      case 171: // value
      case 175: // map_value
      case 213: // socket_type
      case 216: // outbound_interface_value
      case 226: // db_type
      case 307: // hr_mode
      case 453: // ncr_protocol_value
      case 461: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 155: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 154: // "floating point"
        value.copy< double > (that.value);
        break;

      case 153: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 152: // "constant string"
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
            case 152: // "constant string"

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 153: // "integer"

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 154: // "floating point"

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 155: // "boolean"

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 171: // value

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 175: // map_value

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 213: // socket_type

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 216: // outbound_interface_value

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 226: // db_type

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 307: // hr_mode

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 453: // ncr_protocol_value

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 461: // replace_client_name_value

#line 230 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 171: // value
      case 175: // map_value
      case 213: // socket_type
      case 216: // outbound_interface_value
      case 226: // db_type
      case 307: // hr_mode
      case 453: // ncr_protocol_value
      case 461: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 155: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 154: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 153: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 152: // "constant string"
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
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 284 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 295 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 317 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 326 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 335 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 350 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 365 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 389 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 396 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 452 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 653 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1437 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1465 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1503 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1512 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1521 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1682 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 857 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1691 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 875 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1026 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1925 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1027 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1048 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1114 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1130 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1149 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 347:
#line 1214 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2145 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1236 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1259 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1304 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1316 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1329 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2269 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2318 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2336 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1391 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2371 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1414 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2419 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2447 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2457 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1570 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2715 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2886 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1821 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1843 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3058 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1859 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1862 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1874 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1910 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1924 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3228 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3245 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3263 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1996 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 2005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3293 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3328 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3346 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3350 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -734;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     285,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,    41,    19,    42,    44,    48,    56,
      82,   100,   112,   121,   129,   143,   163,   185,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,    19,    14,     8,    62,    31,   155,
       9,   332,   157,     3,    45,   -37,   334,    85,  -734,   192,
     230,   237,   262,   270,  -734,  -734,  -734,  -734,  -734,   279,
    -734,    71,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   280,
     308,  -734,  -734,  -734,  -734,  -734,   309,   311,   312,   314,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
     315,  -734,  -734,  -734,    87,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,   321,  -734,   126,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,   322,   323,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,   144,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,   150,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,   320,   327,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   325,  -734,
    -734,   331,  -734,  -734,  -734,   336,  -734,  -734,   328,   335,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,   338,   341,  -734,  -734,  -734,  -734,   339,
     354,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,   159,  -734,  -734,  -734,   355,  -734,  -734,
     360,  -734,   363,   364,  -734,  -734,   366,   367,   370,  -734,
    -734,  -734,  -734,  -734,   191,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,   197,  -734,  -734,  -734,    19,    19,  -734,   223,   372,
     375,   377,   380,   381,  -734,     8,  -734,   384,   238,   239,
     391,   394,   395,   400,   401,   253,   256,   257,   261,   404,
     407,   409,   411,   418,   433,   434,   435,   436,   451,   303,
     453,   454,    62,  -734,   455,   456,   457,   307,    31,  -734,
     460,   461,   462,   463,   464,   465,   468,   326,   319,   471,
     472,   476,   477,   155,  -734,   479,     9,  -734,   483,   484,
     485,   488,   489,   490,   491,   492,  -734,   332,  -734,   493,
     494,   346,   496,   497,   500,   351,  -734,     3,   503,   353,
     356,  -734,    45,   505,   506,   -13,  -734,   357,   509,   510,
     362,   512,   365,   368,   513,   515,   369,   371,   373,   516,
     521,   334,  -734,   523,    85,  -734,  -734,  -734,   525,   524,
     526,    19,    19,    19,  -734,   527,  -734,  -734,   378,   383,
     385,   529,   531,  -734,  -734,  -734,  -734,   534,   535,   536,
     537,   538,   392,   541,   542,   543,   544,  -734,   545,   546,
    -734,   549,   167,   242,  -734,  -734,   397,   398,   403,   551,
     405,   406,   408,  -734,  -734,    20,   410,   554,   556,  -734,
     412,  -734,   549,   413,   414,   415,   416,   417,   419,   420,
    -734,   421,   422,  -734,   423,   424,   425,  -734,  -734,   426,
    -734,  -734,  -734,   427,    19,  -734,  -734,   428,   429,  -734,
     430,  -734,  -734,    16,   439,  -734,  -734,  -734,   124,   431,
    -734,   565,  -734,    19,    62,    85,  -734,  -734,  -734,    31,
    -734,  -734,  -734,   255,   255,   577,   578,   579,   580,  -734,
    -734,  -734,   169,   581,   582,    90,    80,   334,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   583,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   584,   441,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,   585,  -734,   201,   228,   231,  -734,  -734,  -734,  -734,
     539,   589,   590,   591,   592,  -734,  -734,   593,   594,   595,
     596,  -734,   232,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
     254,  -734,   597,   598,  -734,  -734,   599,   601,  -734,  -734,
     600,   604,  -734,  -734,   602,   606,  -734,  -734,  -734,  -734,
    -734,  -734,    26,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
     137,  -734,  -734,   605,   607,  -734,   608,   609,   610,   611,
     612,   613,   258,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,   260,  -734,  -734,  -734,   269,
     450,  -734,   614,   615,  -734,  -734,   616,   618,  -734,  -734,
     617,  -734,   153,  -734,  -734,  -734,  -734,   619,   620,   622,
     623,   466,   473,   478,   474,   480,   626,   628,   481,   482,
     486,   487,   255,  -734,  -734,   155,  -734,   577,     3,  -734,
     578,    45,  -734,   579,   196,  -734,   580,   169,  -734,    70,
     581,  -734,   -37,  -734,   582,   495,   498,   499,   501,   502,
     504,    90,  -734,   632,   633,    80,  -734,  -734,  -734,   634,
     635,     9,  -734,   583,   332,  -734,   584,   637,  -734,    64,
     585,  -734,   293,   507,   508,   511,  -734,  -734,  -734,  -734,
    -734,   514,   518,  -734,  -734,  -734,  -734,  -734,   273,  -734,
     636,  -734,   638,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,   277,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,   639,   640,  -734,  -734,  -734,
    -734,   298,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
     519,   520,  -734,  -734,   522,   300,  -734,   641,  -734,   528,
    -734,   646,  -734,  -734,  -734,  -734,  -734,   301,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,   196,  -734,   649,  -734,
      70,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   652,   548,
     654,    64,  -734,  -734,   532,  -734,   656,  -734,   540,  -734,
    -734,   655,  -734,  -734,   209,  -734,   -12,   655,  -734,  -734,
     660,   661,   663,   302,  -734,  -734,  -734,  -734,  -734,  -734,
     664,   547,   550,   553,   -12,  -734,   552,  -734,  -734,  -734,
    -734,  -734
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   115,     9,   235,    11,   388,    13,
     412,    15,   313,    17,   321,    19,   358,    21,   200,    23,
     498,    25,   555,    27,    45,    39,     0,     0,     0,     0,
       0,   414,     0,   323,   360,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   553,   547,   549,   551,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   104,     0,
       0,   433,   435,   437,   128,   130,     0,     0,     0,     0,
     227,   311,   350,   284,   400,   402,   178,   459,   192,   211,
       0,   483,   496,    97,     0,    70,    72,    73,    74,    75,
      90,    91,    78,    79,    80,    81,    85,    86,    76,    77,
      83,    84,    95,    96,    92,    93,    94,    82,    87,    88,
      89,   117,   119,   123,     0,   114,     0,   106,   108,   109,
     110,   111,   112,   113,   265,   267,   269,   380,   263,   271,
     273,     0,     0,   277,   275,   404,   455,   262,   239,   240,
     241,   253,     0,   237,   244,   257,   258,   259,   245,   246,
     249,   251,   247,   248,   242,   243,   260,   261,   250,   254,
     255,   256,   252,   398,   397,   394,   393,     0,   390,   392,
     395,   396,   453,   441,   443,   447,   445,   451,   449,   439,
     432,   426,   430,   431,     0,   415,   416,   427,   428,   429,
     423,   418,   424,   420,   421,   422,   425,   419,     0,   340,
     164,     0,   344,   342,   347,     0,   336,   337,     0,   324,
     325,   327,   339,   328,   329,   330,   346,   331,   332,   333,
     334,   335,   374,     0,     0,   372,   373,   376,   377,     0,
     361,   362,   364,   365,   366,   367,   368,   369,   370,   371,
     207,   209,   204,     0,   202,   205,   206,     0,   520,   522,
       0,   525,     0,     0,   529,   533,     0,     0,     0,   538,
     545,   518,   516,   517,     0,   500,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     560,     0,   557,   559,    44,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    55,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,     0,     0,   389,     0,     0,
       0,     0,     0,     0,     0,     0,   413,     0,   314,     0,
       0,     0,     0,     0,     0,     0,   322,     0,     0,     0,
       0,   359,     0,     0,     0,     0,   201,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   499,     0,     0,   556,    48,    41,     0,     0,
       0,     0,     0,     0,    59,     0,   102,   103,     0,     0,
       0,     0,     0,    98,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   482,     0,     0,
      71,     0,     0,     0,   127,   107,     0,     0,     0,     0,
       0,     0,     0,   282,   283,     0,     0,     0,     0,   238,
       0,   391,     0,     0,     0,     0,     0,     0,     0,     0,
     417,     0,     0,   338,     0,     0,     0,   349,   326,     0,
     378,   379,   363,     0,     0,   203,   519,     0,     0,   524,
       0,   527,   528,     0,     0,   535,   536,   537,     0,     0,
     501,     0,   558,     0,     0,     0,   548,   550,   552,     0,
     434,   436,   438,     0,     0,   229,   315,   352,   286,    38,
     401,   403,     0,     0,   194,     0,     0,     0,    49,   118,
     121,   122,   120,   125,   126,   124,   266,   268,   270,   382,
     264,   272,   274,   279,   280,   281,   278,   276,   406,     0,
     399,   454,   442,   444,   448,   446,   452,   450,   440,   341,
     165,   345,   343,   348,   375,   208,   210,   521,   523,   526,
     531,   532,   530,   534,   540,   541,   542,   543,   544,   539,
     546,     0,    42,     0,     0,     0,   151,   157,   159,   161,
       0,     0,     0,     0,     0,   174,   176,     0,     0,     0,
       0,   150,     0,   132,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   145,   146,   147,   148,   144,   149,
       0,   233,     0,   230,   231,   319,     0,   316,   317,   356,
       0,   353,   354,   290,     0,   287,   288,   187,   188,   189,
     190,   191,     0,   180,   182,   183,   184,   185,   186,   463,
       0,   461,   198,     0,   195,   196,     0,     0,     0,     0,
       0,     0,     0,   213,   215,   216,   217,   218,   219,   220,
     492,   494,   491,   489,   490,     0,   485,   487,   488,     0,
      51,   386,     0,   383,   384,   410,     0,   407,   408,   457,
       0,   564,     0,   562,    67,   554,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   131,     0,   228,     0,   323,   312,
       0,   360,   351,     0,     0,   285,     0,     0,   179,   465,
       0,   460,     0,   193,     0,     0,     0,     0,     0,     0,
       0,     0,   212,     0,     0,     0,   484,   497,    53,     0,
      52,     0,   381,     0,   414,   405,     0,     0,   456,     0,
       0,   561,     0,     0,     0,     0,   163,   166,   167,   168,
     169,     0,     0,   170,   171,   172,   173,   133,     0,   232,
       0,   318,     0,   355,   310,   307,   297,   298,   300,   294,
     295,   296,   306,   305,     0,   292,   299,   308,   309,   301,
     302,   303,   304,   289,   181,   480,   478,   479,   471,   472,
     476,   477,   473,   474,   475,     0,   466,   467,   469,   470,
     462,     0,   197,   221,   222,   223,   224,   225,   226,   214,
       0,     0,   486,    50,     0,     0,   385,     0,   409,     0,
     578,     0,   576,   574,   568,   572,   573,     0,   566,   570,
     571,   569,   563,   153,   154,   155,   156,   152,   158,   160,
     162,   175,   177,   234,   320,   357,     0,   291,     0,   464,
       0,   199,   493,   495,    54,   387,   411,   458,     0,     0,
       0,     0,   565,   293,     0,   468,     0,   575,     0,   567,
     481,     0,   577,   582,     0,   580,     0,     0,   579,   590,
       0,     0,     0,     0,   584,   586,   587,   588,   589,   581,
       0,     0,     0,     0,     0,   583,     0,   592,   593,   594,
     585,   591
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,   -51,  -734,   184,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,   181,  -734,  -734,  -734,
     -66,  -734,  -734,  -734,   340,  -734,  -734,  -734,  -734,   156,
     333,   -23,   -21,     0,  -734,  -734,     6,  -734,  -734,   138,
     342,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,   168,   -55,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   -73,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,   -50,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,   -45,  -734,  -734,  -734,   -36,
     317,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   -35,  -734,
    -734,  -734,  -734,  -734,  -734,  -733,  -734,  -734,  -734,    -8,
    -734,  -734,  -734,    -5,   374,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -727,  -734,  -734,  -734,   -25,  -734,  -721,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   -10,  -734,
    -734,  -147,   -61,  -734,  -734,  -734,  -734,  -734,     2,  -734,
    -734,  -734,    11,  -734,   358,  -734,   -68,  -734,  -734,  -734,
    -734,  -734,   -62,  -734,  -734,  -734,  -734,  -734,   -17,  -734,
    -734,  -734,    10,  -734,  -734,  -734,    15,  -734,   349,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
     -15,  -734,  -734,  -734,   -19,   386,  -734,  -734,   -54,  -734,
     -34,  -734,  -734,  -734,  -734,  -734,   -16,  -734,  -734,  -734,
      -9,  -734,   379,   -46,  -734,   -11,  -734,    -1,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -716,  -734,  -734,  -734,  -734,
    -734,  -734,    17,  -734,  -734,  -734,  -131,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,    -4,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,   217,   347,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,
    -734,  -734,  -734,  -734,  -734,  -734,  -734,  -734,   244,   348,
    -734,  -734,  -734,    -6,  -734,  -734,  -130,  -734,  -734,  -734,
    -734,  -734,  -734,  -142,  -734,  -734,  -164,  -734,  -734,  -734,
    -734,  -734
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   550,
      82,    83,    39,    64,    79,    80,   559,   710,   779,   780,
     123,    41,    66,    91,    92,    93,   329,    43,    67,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   337,   156,
     157,    45,    68,   158,   364,   159,   365,   562,   160,   366,
     565,   161,   133,   343,   134,   344,   632,   633,   634,   727,
     887,   635,   728,   636,   729,   637,   730,   638,   247,   400,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   736,
     649,   737,   135,   355,   672,   673,   674,   675,   676,   677,
     678,   136,   357,   683,   684,   685,   762,    59,    75,   283,
     284,   285,   413,   286,   414,   137,   358,   692,   693,   694,
     695,   696,   697,   698,   699,   138,   349,   652,   653,   654,
     745,    47,    69,   182,   183,   184,   374,   185,   370,   186,
     371,   187,   372,   188,   375,   189,   376,   190,   380,   191,
     379,   576,   192,   193,   139,   352,   664,   665,   666,   754,
     824,   825,   140,   350,    53,    72,   656,   657,   658,   748,
      55,    73,   248,   249,   250,   251,   252,   253,   254,   399,
     255,   403,   256,   402,   257,   258,   404,   259,   141,   351,
     660,   661,   662,   751,    57,    74,   269,   270,   271,   272,
     273,   408,   274,   275,   276,   277,   195,   373,   712,   713,
     714,   781,    49,    70,   207,   208,   209,   385,   142,   353,
     143,   354,   198,   381,   716,   717,   718,   784,    51,    71,
     224,   225,   226,   144,   340,   145,   341,   146,   342,   230,
     395,   231,   389,   232,   390,   233,   392,   234,   391,   235,
     394,   236,   393,   237,   388,   202,   382,   720,   787,   147,
     356,   680,   681,   759,   845,   846,   847,   848,   849,   898,
     148,   149,   360,   705,   706,   707,   773,   708,   774,   150,
     361,    61,    76,   304,   305,   306,   307,   418,   308,   419,
     309,   310,   421,   311,   312,   313,   424,   602,   314,   425,
     315,   316,   317,   318,   429,   609,   319,   430,    94,   331,
      95,   332,    96,   333,    97,   330,    63,    77,   321,   322,
     323,   433,   722,   723,   789,   877,   878,   879,   880,   910,
     881,   908,   924,   925,   926,   933,   934,   935,   940,   936,
     937,   938
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   266,   155,   177,   204,   220,   267,   246,   265,   282,
     301,   238,   268,    78,   162,   196,   210,   222,    84,   260,
     278,   820,   302,   199,    29,   227,    30,   821,    31,   757,
     239,   600,   758,   823,   163,   197,   211,   223,   832,   261,
     279,    28,   303,   151,   152,   205,   178,   153,   179,    40,
     154,    42,   194,   206,   221,    44,   280,   281,   200,   240,
     228,   241,   242,    46,   112,   243,   244,   245,   201,   180,
     229,   114,   115,    98,   335,   181,   203,   114,   115,   336,
     280,   281,    99,   100,   101,   102,   103,   104,   105,    48,
     362,   174,   101,   102,   103,   363,   573,   574,   575,   114,
     115,   240,   262,   241,   242,   263,   264,    50,   106,   107,
     108,   109,   110,   114,   115,    89,   111,   112,   929,    52,
     240,   930,   931,   932,   111,   112,   240,   113,    54,   368,
     114,   115,   114,   115,   369,    85,    56,   601,   114,   115,
     760,   116,   117,   761,    86,    87,    88,   383,   114,   115,
      58,   835,   384,   386,   118,    89,   790,   119,   387,   791,
      89,    89,   415,   820,   120,   121,    81,   416,   122,   821,
      60,    32,    33,    34,    35,   823,   100,   101,   102,   103,
     832,   560,   561,    89,   700,   701,   686,   687,   688,   689,
     690,   691,    62,   870,   431,   871,   872,    89,   324,   432,
     434,   106,   107,   108,   362,   435,   164,   165,   166,   724,
     112,   111,   927,   320,    89,   928,    89,   100,   101,   102,
     103,   167,    89,   114,   115,   168,   169,   170,   171,   172,
     173,   434,    89,   325,   368,   742,   725,   174,   175,   726,
     743,   326,   106,   107,   108,   176,   110,   604,   605,   606,
     607,   112,   240,   667,   668,   669,   670,   742,   671,   563,
     564,   771,   744,   775,   114,   115,   772,   169,   776,    90,
     327,   173,   431,   328,   436,   437,   383,   777,   174,   608,
     896,   893,   616,   334,   338,   897,   176,   617,   618,   619,
     620,   621,   622,   623,   624,   625,   626,   627,   628,   629,
     630,   415,   155,   386,   911,   944,   901,    89,   905,   912,
     945,   240,   339,   345,   162,   346,   347,   177,   348,   359,
     204,   883,   884,   885,   886,   367,   377,   378,   396,   196,
     397,   220,   210,   398,   163,   401,   406,   199,   407,   266,
     405,   246,   409,   222,   267,   410,   265,   411,    89,   197,
     268,   227,   211,   260,   101,   102,   103,   412,   278,   417,
     178,   205,   179,   223,   420,   301,   194,   422,   423,   206,
     426,   427,   200,   261,   428,   438,   439,   302,   279,   440,
     221,   441,   201,   180,   442,   443,   228,   112,   445,   181,
     536,   537,   538,   446,   447,   448,   229,   303,   449,   450,
     114,   115,   114,   115,   451,   452,   453,    89,   457,   454,
     455,   458,   212,   459,   456,   460,   213,   214,   215,   216,
     217,   218,   461,   219,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   462,   463,   464,
     465,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   466,   467,   468,   469,   471,
     472,   473,   474,   596,   476,   477,   478,   479,   480,   481,
     639,   639,   482,   155,   484,   485,   486,   631,   631,   483,
     487,   488,   612,   490,    89,   162,    89,   492,   493,   494,
     702,   301,   495,   496,   497,   498,   499,   501,   502,   503,
     504,   505,   703,   302,   506,   163,   507,   509,   510,   513,
     514,   511,   516,   517,   518,   519,   520,   523,   521,   524,
     528,   522,   704,   303,   525,   529,   526,   531,   527,   533,
     540,   534,   719,   535,   539,   541,   543,   542,   544,   545,
     546,   547,   548,   731,   551,    30,   552,   553,   554,   566,
     567,   555,   556,   557,   558,   568,   569,   570,   571,   578,
     572,   603,   577,   579,   580,   582,   583,   584,   585,   586,
     611,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     597,   598,   599,   610,   651,   655,   659,   663,   679,   682,
     711,   715,   721,   732,   733,   734,   735,   738,   739,   740,
     741,   747,   778,   746,   750,   749,   752,   753,   755,   756,
     764,   763,   765,   766,   767,   768,   769,   770,   783,   796,
     782,   786,   785,   792,   793,   788,   794,   795,   797,   799,
     801,   798,   802,   800,   803,   804,   860,   861,   864,   805,
     863,   869,   806,   900,   894,   549,   895,   899,   853,   906,
     909,   854,   855,   914,   856,   857,   916,   858,   918,   888,
     889,   921,   923,   890,   941,   942,   891,   943,   946,   639,
     892,   902,   903,   581,   904,   444,   631,   615,   266,   177,
     907,   819,   246,   267,   920,   265,   837,   807,   814,   268,
     613,   196,   922,   836,   260,   470,   282,   278,   838,   199,
     827,   917,   947,   948,   951,   840,   949,   834,   829,   702,
     475,   197,   650,   842,   261,   204,   874,   279,   220,   852,
     828,   703,   178,   873,   179,   841,   851,   210,   194,   822,
     222,   815,   515,   816,   200,   875,   859,   826,   227,   809,
     808,   704,   839,   830,   201,   180,   833,   211,   843,   913,
     223,   181,   811,   831,   817,   876,   205,   489,   844,   810,
     818,   512,   865,   813,   206,   508,   812,   221,   866,   915,
     868,   862,   491,   228,   709,   867,   500,   850,   530,   614,
     950,   919,   532,   229,   882,   939,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   819,     0,     0,     0,   837,     0,     0,
     814,     0,     0,     0,   836,     0,     0,     0,   874,   838,
       0,     0,   827,     0,     0,   873,   840,     0,     0,     0,
     829,     0,     0,     0,   842,     0,     0,   875,     0,     0,
       0,     0,   828,     0,     0,     0,   841,     0,     0,     0,
       0,   822,     0,   815,     0,   816,     0,   876,     0,   826,
       0,     0,     0,   839,     0,   830,     0,     0,     0,   843,
       0,     0,     0,     0,     0,   831,   817,     0,     0,   844,
       0,     0,   818
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    74,    68,    69,    70,    71,    74,    73,    74,    75,
      76,    72,    74,    64,    68,    69,    70,    71,    10,    73,
      74,   754,    76,    69,     5,    71,     7,   754,     9,     3,
      27,    15,     6,   754,    68,    69,    70,    71,   754,    73,
      74,     0,    76,    12,    13,    70,    69,    16,    69,     7,
      19,     7,    69,    70,    71,     7,    93,    94,    69,    56,
      71,    58,    59,     7,    55,    62,    63,    64,    69,    69,
      71,    68,    69,    11,     3,    69,    67,    68,    69,     8,
      93,    94,    20,    21,    22,    23,    24,    25,    26,     7,
       3,    82,    22,    23,    24,     8,    76,    77,    78,    68,
      69,    56,    57,    58,    59,    60,    61,     7,    46,    47,
      48,    49,    50,    68,    69,   152,    54,    55,   130,     7,
      56,   133,   134,   135,    54,    55,    56,    65,     7,     3,
      68,    69,    68,    69,     8,   127,     7,   121,    68,    69,
       3,    79,    80,     6,   136,   137,   138,     3,    68,    69,
       7,    81,     8,     3,    92,   152,     3,    95,     8,     6,
     152,   152,     3,   896,   102,   103,   152,     8,   106,   896,
       7,   152,   153,   154,   155,   896,    21,    22,    23,    24,
     896,    14,    15,   152,   104,   105,    96,    97,    98,    99,
     100,   101,     7,   129,     3,   131,   132,   152,     6,     8,
       3,    46,    47,    48,     3,     8,    51,    52,    53,     8,
      55,    54,     3,   128,   152,     6,   152,    21,    22,    23,
      24,    66,   152,    68,    69,    70,    71,    72,    73,    74,
      75,     3,   152,     3,     3,     3,     8,    82,    83,     8,
       8,     4,    46,    47,    48,    90,    50,   123,   124,   125,
     126,    55,    56,    84,    85,    86,    87,     3,    89,    17,
      18,     3,     8,     3,    68,    69,     8,    71,     8,   335,
       8,    75,     3,     3,   325,   326,     3,     8,    82,   155,
       3,     8,    27,     4,     4,     8,    90,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     3,   368,     3,     3,     3,     8,   152,     8,     8,
       8,    56,     4,     4,   368,     4,     4,   383,     4,     4,
     386,    28,    29,    30,    31,     4,     4,     4,     8,   383,
       3,   397,   386,     8,   368,     4,     8,   383,     3,   412,
       4,   407,     4,   397,   412,     4,   412,     8,   152,   383,
     412,   397,   386,   407,    22,    23,    24,     3,   412,     4,
     383,   386,   383,   397,     4,   431,   383,     4,     4,   386,
       4,     4,   383,   407,     4,   152,     4,   431,   412,     4,
     397,     4,   383,   383,     4,     4,   397,    55,     4,   383,
     441,   442,   443,   155,   155,     4,   397,   431,     4,     4,
      68,    69,    68,    69,     4,     4,   153,   152,     4,   153,
     153,     4,    80,     4,   153,     4,    84,    85,    86,    87,
      88,    89,     4,    91,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     4,     4,     4,
       4,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,     4,   153,     4,     4,     4,
       4,     4,   155,   514,     4,     4,     4,     4,     4,     4,
     543,   544,     4,   539,   155,     4,     4,   543,   544,   153,
       4,     4,   533,     4,   152,   539,   152,     4,     4,     4,
     556,   557,     4,     4,     4,     4,     4,     4,     4,   153,
       4,     4,   556,   557,     4,   539,   155,     4,   155,     4,
       4,   155,   155,     4,     4,   153,     4,     4,   153,     4,
       4,   153,   556,   557,   155,     4,   155,     4,   155,     4,
     152,     7,    91,     7,     7,   152,     7,   152,     7,     5,
       5,     5,     5,     4,   152,     7,     5,     5,     5,   152,
     152,     7,     7,     7,     5,   152,     5,   152,   152,     5,
     152,   122,   152,     7,   152,   152,   152,   152,   152,   152,
       5,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   152,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     4,     4,     4,     4,     4,     4,     3,   153,
       6,     3,     6,     4,     4,     8,     4,     4,   155,   155,
       4,   153,     4,   153,   153,   153,     4,     4,     3,   153,
       6,     4,   155,     3,     8,   461,     8,     8,   153,     8,
       4,   153,   153,     4,   153,   153,     4,   153,     4,   152,
     152,     5,     7,   152,     4,     4,   152,     4,     4,   742,
     152,   152,   152,   492,   152,   335,   742,   539,   751,   745,
     152,   754,   748,   751,   152,   751,   759,   742,   754,   751,
     534,   745,   152,   759,   748,   362,   762,   751,   759,   745,
     754,   153,   155,   153,   152,   759,   153,   757,   754,   775,
     368,   745,   544,   759,   748,   781,   789,   751,   784,   764,
     754,   775,   745,   789,   745,   759,   762,   781,   745,   754,
     784,   754,   415,   754,   745,   789,   771,   754,   784,   747,
     745,   775,   759,   754,   745,   745,   756,   781,   759,   896,
     784,   745,   750,   754,   754,   789,   781,   383,   759,   748,
     754,   412,   781,   753,   781,   407,   751,   784,   783,   900,
     786,   775,   386,   784,   557,   784,   397,   760,   431,   535,
     944,   911,   434,   784,   790,   927,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   896,    -1,    -1,    -1,   900,    -1,    -1,
     896,    -1,    -1,    -1,   900,    -1,    -1,    -1,   911,   900,
      -1,    -1,   896,    -1,    -1,   911,   900,    -1,    -1,    -1,
     896,    -1,    -1,    -1,   900,    -1,    -1,   911,    -1,    -1,
      -1,    -1,   896,    -1,    -1,    -1,   900,    -1,    -1,    -1,
      -1,   896,    -1,   896,    -1,   896,    -1,   911,    -1,   896,
      -1,    -1,    -1,   900,    -1,   896,    -1,    -1,    -1,   900,
      -1,    -1,    -1,    -1,    -1,   896,   896,    -1,    -1,   900,
      -1,    -1,   896
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     5,
       7,     9,   152,   153,   154,   155,   171,   172,   173,   178,
       7,   187,     7,   193,     7,   207,     7,   287,     7,   368,
       7,   384,     7,   320,     7,   326,     7,   350,     7,   263,
       7,   437,     7,   472,   179,   174,   188,   194,   208,   288,
     369,   385,   321,   327,   351,   264,   438,   473,   171,   180,
     181,   152,   176,   177,    10,   127,   136,   137,   138,   152,
     186,   189,   190,   191,   464,   466,   468,   470,    11,    20,
      21,    22,    23,    24,    25,    26,    46,    47,    48,    49,
      50,    54,    55,    65,    68,    69,    79,    80,    92,    95,
     102,   103,   106,   186,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   218,   220,   248,   257,   271,   281,   310,
     318,   344,   374,   376,   389,   391,   393,   415,   426,   427,
     435,    12,    13,    16,    19,   186,   205,   206,   209,   211,
     214,   217,   374,   376,    51,    52,    53,    66,    70,    71,
      72,    73,    74,    75,    82,    83,    90,   186,   197,   198,
     199,   202,   289,   290,   291,   293,   295,   297,   299,   301,
     303,   305,   308,   309,   344,   362,   374,   376,   378,   389,
     391,   393,   411,    67,   186,   303,   344,   370,   371,   372,
     374,   376,    80,    84,    85,    86,    87,    88,    89,    91,
     186,   344,   374,   376,   386,   387,   388,   389,   391,   393,
     395,   397,   399,   401,   403,   405,   407,   409,   318,    27,
      56,    58,    59,    62,    63,    64,   186,   234,   328,   329,
     330,   331,   332,   333,   334,   336,   338,   340,   341,   343,
     374,   376,    57,    60,    61,   186,   234,   332,   338,   352,
     353,   354,   355,   356,   358,   359,   360,   361,   374,   376,
      93,    94,   186,   265,   266,   267,   269,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   186,   374,   376,   439,   440,   441,   442,   444,   446,
     447,   449,   450,   451,   454,   456,   457,   458,   459,   462,
     128,   474,   475,   476,     6,     3,     4,     8,     3,   192,
     471,   465,   467,   469,     4,     3,     8,   204,     4,     4,
     390,   392,   394,   219,   221,     4,     4,     4,     4,   282,
     319,   345,   311,   375,   377,   249,   416,   258,   272,     4,
     428,   436,     3,     8,   210,   212,   215,     4,     3,     8,
     294,   296,   298,   363,   292,   300,   302,     4,     4,   306,
     304,   379,   412,     3,     8,   373,     3,     8,   410,   398,
     400,   404,   402,   408,   406,   396,     8,     3,     8,   335,
     235,     4,   339,   337,   342,     4,     8,     3,   357,     4,
       4,     8,     3,   268,   270,     3,     8,     4,   443,   445,
       4,   448,     4,     4,   452,   455,     4,     4,     4,   460,
     463,     3,     8,   477,     3,     8,   171,   171,   152,     4,
       4,     4,     4,     4,   190,     4,   155,   155,     4,     4,
       4,     4,     4,   153,   153,   153,   153,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   153,     4,     4,
     196,     4,     4,     4,   155,   206,     4,     4,     4,     4,
       4,     4,     4,   153,   155,     4,     4,     4,     4,   290,
       4,   371,     4,     4,     4,     4,     4,     4,     4,     4,
     388,     4,     4,   153,     4,     4,     4,   155,   330,     4,
     155,   155,   354,     4,     4,   266,   155,     4,     4,   153,
       4,   153,   153,     4,     4,   155,   155,   155,     4,     4,
     440,     4,   475,     4,     7,     7,   171,   171,   171,     7,
     152,   152,   152,     7,     7,     5,     5,     5,     5,   173,
     175,   152,     5,     5,     5,     7,     7,     7,     5,   182,
      14,    15,   213,    17,    18,   216,   152,   152,   152,     5,
     152,   152,   152,    76,    77,    78,   307,   152,     5,     7,
     152,   182,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   171,   152,   152,   152,
      15,   121,   453,   122,   123,   124,   125,   126,   155,   461,
     152,     5,   171,   195,   474,   205,    27,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,   186,   222,   223,   224,   227,   229,   231,   233,   234,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   246,
     222,     7,   283,   284,   285,     7,   322,   323,   324,     7,
     346,   347,   348,     7,   312,   313,   314,    84,    85,    86,
      87,    89,   250,   251,   252,   253,   254,   255,   256,     7,
     417,   418,     7,   259,   260,   261,    96,    97,    98,    99,
     100,   101,   273,   274,   275,   276,   277,   278,   279,   280,
     104,   105,   186,   374,   376,   429,   430,   431,   433,   439,
     183,     7,   364,   365,   366,     7,   380,   381,   382,    91,
     413,     7,   478,   479,     8,     8,     8,   225,   228,   230,
     232,     4,     4,     4,     4,     4,   245,   247,     4,     4,
       4,     4,     3,     8,     8,   286,     6,     3,   325,     6,
       3,   349,     6,     3,   315,     6,     3,     3,     6,   419,
       3,     6,   262,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   432,   434,     3,     8,     8,   152,   184,
     185,   367,     6,     3,   383,     6,     3,   414,     8,   480,
       3,     6,     4,     4,     4,     4,   153,   155,   153,   155,
     153,     4,     4,   153,   153,   153,   155,   223,   289,   285,
     328,   324,   352,   348,   186,   197,   198,   199,   202,   234,
     281,   299,   303,   305,   316,   317,   344,   374,   376,   389,
     391,   393,   411,   314,   251,    81,   186,   234,   318,   344,
     374,   376,   389,   391,   393,   420,   421,   422,   423,   424,
     418,   265,   261,   153,   153,   153,   153,   153,   153,   274,
       4,     4,   430,     6,     3,   370,   366,   386,   382,     4,
     129,   131,   132,   186,   234,   374,   376,   481,   482,   483,
     484,   486,   479,    28,    29,    30,    31,   226,   152,   152,
     152,   152,   152,     8,     8,     8,     3,     8,   425,     8,
       3,     8,   152,   152,   152,     8,     8,   152,   487,     4,
     485,     3,     8,   317,     4,   422,     4,   153,     4,   482,
     152,     5,   152,     7,   488,   489,   490,     3,     6,   130,
     133,   134,   135,   491,   492,   493,   495,   496,   497,   489,
     494,     4,     4,     4,     3,     8,     4,   155,   153,   153,
     492,   152
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   156,   158,   157,   159,   157,   160,   157,   161,   157,
     162,   157,   163,   157,   164,   157,   165,   157,   166,   157,
     167,   157,   168,   157,   169,   157,   170,   157,   171,   171,
     171,   171,   171,   171,   171,   172,   174,   173,   175,   176,
     176,   177,   177,   179,   178,   180,   180,   181,   181,   183,
     182,   184,   184,   185,   185,   186,   188,   187,   189,   189,
     190,   190,   190,   190,   190,   190,   192,   191,   194,   193,
     195,   195,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   197,   198,
     199,   200,   201,   202,   204,   203,   205,   205,   206,   206,
     206,   206,   206,   206,   206,   208,   207,   210,   209,   212,
     211,   213,   213,   215,   214,   216,   216,   217,   219,   218,
     221,   220,   222,   222,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   225,   224,   226,   226,   226,   226,   228,   227,   230,
     229,   232,   231,   233,   235,   234,   236,   237,   238,   239,
     240,   241,   242,   243,   245,   244,   247,   246,   249,   248,
     250,   250,   251,   251,   251,   251,   251,   252,   253,   254,
     255,   256,   258,   257,   259,   259,   260,   260,   262,   261,
     264,   263,   265,   265,   265,   266,   266,   268,   267,   270,
     269,   272,   271,   273,   273,   274,   274,   274,   274,   274,
     274,   275,   276,   277,   278,   279,   280,   282,   281,   283,
     283,   284,   284,   286,   285,   288,   287,   289,   289,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   292,   291,   294,   293,   296,   295,   298,
     297,   300,   299,   302,   301,   304,   303,   306,   305,   307,
     307,   307,   308,   309,   311,   310,   312,   312,   313,   313,
     315,   314,   316,   316,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   319,   318,   321,   320,   322,   322,   323,   323,   325,
     324,   327,   326,   328,   328,   329,   329,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   331,   332,   333,
     335,   334,   337,   336,   339,   338,   340,   342,   341,   343,
     345,   344,   346,   346,   347,   347,   349,   348,   351,   350,
     352,   352,   353,   353,   354,   354,   354,   354,   354,   354,
     354,   354,   354,   355,   357,   356,   358,   359,   360,   361,
     363,   362,   364,   364,   365,   365,   367,   366,   369,   368,
     370,   370,   371,   371,   371,   371,   371,   371,   373,   372,
     375,   374,   377,   376,   379,   378,   380,   380,   381,   381,
     383,   382,   385,   384,   386,   386,   387,   387,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   390,   389,   392,   391,   394,   393,   396,
     395,   398,   397,   400,   399,   402,   401,   404,   403,   406,
     405,   408,   407,   410,   409,   412,   411,   414,   413,   416,
     415,   417,   417,   419,   418,   420,   420,   421,   421,   422,
     422,   422,   422,   422,   422,   422,   422,   422,   422,   423,
     425,   424,   426,   428,   427,   429,   429,   430,   430,   430,
     430,   430,   432,   431,   434,   433,   436,   435,   438,   437,
     439,   439,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   441,
     443,   442,   445,   444,   446,   448,   447,   449,   450,   452,
     451,   453,   453,   455,   454,   456,   457,   458,   460,   459,
     461,   461,   461,   461,   461,   463,   462,   465,   464,   467,
     466,   469,   468,   471,   470,   473,   472,   474,   474,   475,
     477,   476,   478,   478,   480,   479,   481,   481,   482,   482,
     482,   482,   482,   482,   482,   483,   485,   484,   487,   486,
     488,   488,   490,   489,   491,   491,   492,   492,   492,   492,
     494,   493,   495,   496,   497
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
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     1,
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
  "\"contact-points\"", "\"keyspace\"", "\"reconnect-wait-time\"",
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
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@32", "keyspace", "$@33",
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
       0,   239,   239,   239,   240,   240,   241,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   246,   246,   247,   247,
     248,   248,   249,   249,   250,   250,   251,   251,   259,   260,
     261,   262,   263,   264,   265,   268,   273,   273,   284,   287,
     288,   291,   295,   302,   302,   309,   310,   313,   317,   324,
     324,   331,   332,   335,   339,   350,   360,   360,   376,   377,
     381,   382,   383,   384,   385,   386,   389,   389,   404,   404,
     413,   414,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   447,   452,
     457,   462,   467,   472,   478,   478,   489,   490,   493,   494,
     495,   496,   497,   498,   499,   502,   502,   511,   511,   521,
     521,   528,   529,   532,   532,   539,   541,   545,   551,   551,
     563,   563,   575,   576,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   598,   598,   605,   606,   607,   608,   611,   611,   619,
     619,   627,   627,   635,   640,   640,   648,   653,   658,   663,
     668,   673,   678,   683,   688,   688,   696,   696,   705,   705,
     715,   716,   719,   720,   721,   722,   723,   726,   731,   736,
     741,   746,   751,   751,   761,   762,   765,   766,   769,   769,
     779,   779,   789,   790,   791,   794,   795,   798,   798,   806,
     806,   814,   814,   825,   826,   829,   830,   831,   832,   833,
     834,   837,   842,   847,   852,   857,   862,   870,   870,   883,
     884,   887,   888,   895,   895,   921,   921,   932,   933,   937,
     938,   939,   940,   941,   942,   943,   944,   945,   946,   947,
     948,   949,   950,   951,   952,   953,   954,   955,   956,   957,
     958,   959,   960,   963,   963,   971,   971,   979,   979,   987,
     987,   995,   995,  1003,  1003,  1011,  1011,  1019,  1019,  1026,
    1027,  1028,  1031,  1036,  1043,  1043,  1054,  1055,  1059,  1060,
    1063,  1063,  1071,  1072,  1075,  1076,  1077,  1078,  1079,  1080,
    1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,
    1091,  1098,  1098,  1111,  1111,  1120,  1121,  1124,  1125,  1130,
    1130,  1145,  1145,  1159,  1160,  1163,  1164,  1167,  1168,  1169,
    1170,  1171,  1172,  1173,  1174,  1175,  1176,  1179,  1181,  1186,
    1188,  1188,  1196,  1196,  1204,  1204,  1212,  1214,  1214,  1222,
    1231,  1231,  1243,  1244,  1249,  1250,  1255,  1255,  1267,  1267,
    1279,  1280,  1285,  1286,  1291,  1292,  1293,  1294,  1295,  1296,
    1297,  1298,  1299,  1302,  1304,  1304,  1312,  1314,  1316,  1321,
    1329,  1329,  1341,  1342,  1345,  1346,  1349,  1349,  1359,  1359,
    1369,  1370,  1373,  1374,  1375,  1376,  1377,  1378,  1381,  1381,
    1389,  1389,  1414,  1414,  1444,  1444,  1454,  1455,  1458,  1459,
    1462,  1462,  1471,  1471,  1480,  1481,  1484,  1485,  1489,  1490,
    1491,  1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,  1500,
    1501,  1502,  1503,  1506,  1506,  1514,  1514,  1522,  1522,  1530,
    1530,  1538,  1538,  1546,  1546,  1554,  1554,  1562,  1562,  1570,
    1570,  1578,  1578,  1586,  1586,  1599,  1599,  1609,  1609,  1620,
    1620,  1630,  1631,  1634,  1634,  1644,  1645,  1648,  1649,  1652,
    1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1664,
    1666,  1666,  1678,  1685,  1685,  1695,  1696,  1699,  1700,  1701,
    1702,  1703,  1706,  1706,  1714,  1714,  1724,  1724,  1736,  1736,
    1746,  1747,  1750,  1751,  1752,  1753,  1754,  1755,  1756,  1757,
    1758,  1759,  1760,  1761,  1762,  1763,  1764,  1765,  1766,  1769,
    1774,  1774,  1782,  1782,  1790,  1795,  1795,  1803,  1808,  1813,
    1813,  1821,  1822,  1825,  1825,  1833,  1838,  1843,  1848,  1848,
    1856,  1859,  1862,  1865,  1868,  1874,  1874,  1884,  1884,  1891,
    1891,  1898,  1898,  1910,  1910,  1920,  1920,  1931,  1932,  1936,
    1940,  1940,  1952,  1953,  1957,  1957,  1965,  1966,  1969,  1970,
    1971,  1972,  1973,  1974,  1975,  1978,  1983,  1983,  1991,  1991,
    2001,  2002,  2005,  2005,  2013,  2014,  2017,  2018,  2019,  2020,
    2023,  2023,  2031,  2036,  2041
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
#line 4547 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2046 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
