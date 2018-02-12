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
      case 168: // value
      case 172: // map_value
      case 210: // socket_type
      case 213: // outbound_interface_value
      case 229: // db_type
      case 306: // hr_mode
      case 452: // ncr_protocol_value
      case 460: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 152: // "boolean"
        value.move< bool > (that.value);
        break;

      case 151: // "floating point"
        value.move< double > (that.value);
        break;

      case 150: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 149: // "constant string"
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
      case 168: // value
      case 172: // map_value
      case 210: // socket_type
      case 213: // outbound_interface_value
      case 229: // db_type
      case 306: // hr_mode
      case 452: // ncr_protocol_value
      case 460: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 152: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 151: // "floating point"
        value.copy< double > (that.value);
        break;

      case 150: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 149: // "constant string"
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
            case 149: // "constant string"

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 150: // "integer"

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 151: // "floating point"

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 152: // "boolean"

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 172: // map_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 210: // socket_type

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 213: // outbound_interface_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 229: // db_type

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 306: // hr_mode

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 452: // ncr_protocol_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 460: // replace_client_name_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 168: // value
      case 172: // map_value
      case 210: // socket_type
      case 213: // outbound_interface_value
      case 229: // db_type
      case 306: // hr_mode
      case 452: // ncr_protocol_value
      case 460: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 152: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 151: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 150: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 149: // "constant string"
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
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 270 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 288 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 302 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 310 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 314 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 332 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 336 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 357 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 362 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 386 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 405 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1310 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1525 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 753 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 758 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1602 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1620 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1629 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1695 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1715 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 877 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 973 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 989 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1021 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1023 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1028 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1950 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1050 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1979 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1989 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2034 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1136 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1200 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1206 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1216 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1218 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1224 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1257 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1261 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2234 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2244 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2253 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2340 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1508 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2614 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1572 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1582 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1593 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2681 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2954 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1824 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1845 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1861 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1867 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3121 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3138 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3175 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3184 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3297 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3305 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 593:
#line 2033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3350 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3354 "dhcp4_parser.cc" // lalr1.cc:859
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
     374,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,    45,    19,    40,    64,    82,   104,
     105,   106,   117,   127,   139,   143,   153,   154,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,    19,  -100,    31,    33,    74,   165,
      42,   173,   126,    92,   253,    14,   313,    58,  -737,   186,
     191,   208,   210,   213,  -737,  -737,  -737,  -737,  -737,   222,
    -737,    61,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   236,
     249,  -737,  -737,  -737,  -737,  -737,  -737,   256,   262,   268,
     281,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,   282,  -737,  -737,  -737,    62,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   296,  -737,    80,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,   300,   308,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,   134,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   146,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   305,   312,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
     319,  -737,  -737,   324,  -737,  -737,  -737,   327,  -737,  -737,
     325,   333,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,   334,   335,  -737,  -737,  -737,
    -737,   337,   338,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,   164,  -737,  -737,  -737,   339,
    -737,  -737,   346,  -737,   347,   353,  -737,  -737,   354,   355,
     358,  -737,  -737,  -737,  -737,  -737,   182,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,   190,  -737,  -737,  -737,    19,    19,  -737,
     167,   360,   363,   370,   371,   373,  -737,    31,  -737,   378,
     232,   233,   383,   388,   390,   391,   392,   394,   192,   251,
     255,   264,   395,   402,   411,   412,   427,   431,   433,   434,
     435,   436,   297,   439,   440,    33,  -737,   441,   442,   444,
     298,    74,  -737,   445,   447,   448,   449,   452,   454,   455,
     310,   311,   460,   461,   462,   463,   165,  -737,   465,    42,
    -737,   466,   467,   469,   470,   471,   474,   475,   476,  -737,
     173,  -737,   478,   479,   336,   480,   481,   483,   340,  -737,
      92,   484,   342,   345,  -737,   253,   486,   487,    -9,  -737,
     349,   489,   494,   352,   495,   356,   375,   499,   500,   372,
     377,   379,   501,   519,   313,  -737,   522,    58,  -737,  -737,
    -737,   526,   525,   527,    19,    19,    19,  -737,   528,  -737,
    -737,   384,   387,   393,   530,   532,   535,  -737,  -737,  -737,
    -737,   536,   538,   539,   540,   541,   397,   542,   544,   545,
     546,  -737,   547,   548,  -737,   551,    15,    79,  -737,  -737,
     403,   408,   409,   554,   413,   414,   415,  -737,  -737,   -12,
     416,   555,   559,  -737,   418,  -737,   551,   419,   420,   421,
     422,   423,   424,   425,  -737,   426,   428,  -737,   429,   430,
     432,  -737,  -737,   437,  -737,  -737,  -737,   438,    19,  -737,
    -737,   443,   446,  -737,   450,  -737,  -737,    23,   457,  -737,
    -737,  -737,    99,   451,  -737,   556,  -737,    19,    33,    58,
    -737,  -737,  -737,    74,  -737,  -737,  -737,   242,   242,   573,
     575,   576,   577,   578,  -737,  -737,  -737,   181,   581,   582,
     107,    26,   313,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,   583,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,   584,   505,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   587,  -737,   203,   221,
     239,  -737,  -737,  -737,  -737,   592,   593,   594,   597,   598,
    -737,  -737,  -737,   240,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,   265,  -737,   599,
     600,  -737,  -737,   601,   603,  -737,  -737,   602,   606,  -737,
    -737,   604,   608,  -737,  -737,   607,   609,  -737,  -737,  -737,
    -737,  -737,  -737,   120,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,   132,  -737,  -737,   610,   611,  -737,   613,   614,   615,
     616,   617,   618,   266,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   284,  -737,  -737,  -737,
     285,   477,  -737,   619,   612,  -737,  -737,   621,   620,  -737,
    -737,   543,  -737,   178,  -737,  -737,  -737,  -737,   624,   625,
     626,   627,   482,   472,   485,   488,   491,   629,   630,   242,
    -737,  -737,   242,  -737,   573,   165,  -737,   575,    92,  -737,
     576,   253,  -737,   577,   389,  -737,   578,   181,  -737,    78,
     581,  -737,    14,  -737,   582,   492,   493,   496,   497,   498,
     502,   107,  -737,   632,   633,    26,  -737,  -737,  -737,   638,
     635,    42,  -737,   583,   173,  -737,   584,   641,  -737,    50,
     587,  -737,   341,   490,   504,   506,  -737,  -737,  -737,  -737,
    -737,   507,   508,  -737,   286,  -737,   293,  -737,   596,  -737,
     642,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,   294,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,   643,   646,  -737,  -737,  -737,  -737,   295,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,   509,   510,
    -737,  -737,   511,   318,  -737,   653,  -737,   513,  -737,   650,
    -737,  -737,  -737,  -737,  -737,   321,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,   389,  -737,   659,  -737,    78,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,   660,   515,   662,
      50,  -737,  -737,   518,  -737,   663,  -737,   520,  -737,  -737,
     664,  -737,  -737,   243,  -737,   -13,   664,  -737,  -737,   666,
     668,   669,   322,  -737,  -737,  -737,  -737,  -737,  -737,   670,
     523,   531,   534,   -13,  -737,   529,  -737,  -737,  -737,  -737,
    -737
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   116,     9,   236,    11,   389,    13,
     413,    15,   314,    17,   322,    19,   359,    21,   201,    23,
     499,    25,   556,    27,    45,    39,     0,     0,     0,     0,
       0,   415,     0,   324,   361,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   554,   548,   550,   552,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   105,     0,
       0,   434,   436,   438,   129,   131,   133,     0,     0,     0,
       0,   228,   312,   351,   285,   401,   403,   179,   460,   193,
     212,     0,   484,   497,    98,     0,    70,    72,    73,    74,
      75,    91,    92,    78,    79,    80,    81,    82,    86,    87,
      76,    77,    84,    85,    96,    97,    93,    94,    95,    83,
      88,    89,    90,   118,   120,   124,     0,   115,     0,   107,
     109,   110,   111,   112,   113,   114,   266,   268,   270,   381,
     264,   272,   274,     0,     0,   278,   276,   405,   456,   263,
     240,   241,   242,   254,     0,   238,   245,   258,   259,   260,
     246,   247,   250,   252,   248,   249,   243,   244,   261,   262,
     251,   255,   256,   257,   253,   399,   398,   395,   394,     0,
     391,   393,   396,   397,   454,   442,   444,   448,   446,   452,
     450,   440,   433,   427,   431,   432,     0,   416,   417,   428,
     429,   430,   424,   419,   425,   421,   422,   423,   426,   420,
       0,   341,   169,     0,   345,   343,   348,     0,   337,   338,
       0,   325,   326,   328,   340,   329,   330,   331,   347,   332,
     333,   334,   335,   336,   375,     0,     0,   373,   374,   377,
     378,     0,   362,   363,   365,   366,   367,   368,   369,   370,
     371,   372,   208,   210,   205,     0,   203,   206,   207,     0,
     521,   523,     0,   526,     0,     0,   530,   534,     0,     0,
       0,   539,   546,   519,   517,   518,     0,   501,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   561,     0,   558,   560,    44,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    55,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   237,     0,     0,
     390,     0,     0,     0,     0,     0,     0,     0,     0,   414,
       0,   315,     0,     0,     0,     0,     0,     0,     0,   323,
       0,     0,     0,     0,   360,     0,     0,     0,     0,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   500,     0,     0,   557,    48,
      41,     0,     0,     0,     0,     0,     0,    59,     0,   103,
     104,     0,     0,     0,     0,     0,     0,    99,   100,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   483,     0,     0,    71,     0,     0,     0,   128,   108,
       0,     0,     0,     0,     0,     0,     0,   283,   284,     0,
       0,     0,     0,   239,     0,   392,     0,     0,     0,     0,
       0,     0,     0,     0,   418,     0,     0,   339,     0,     0,
       0,   350,   327,     0,   379,   380,   364,     0,     0,   204,
     520,     0,     0,   525,     0,   528,   529,     0,     0,   536,
     537,   538,     0,     0,   502,     0,   559,     0,     0,     0,
     549,   551,   553,     0,   435,   437,   439,     0,     0,   135,
     230,   316,   353,   287,    38,   402,   404,     0,     0,   195,
       0,     0,     0,    49,   119,   122,   123,   121,   126,   127,
     125,   267,   269,   271,   383,   265,   273,   275,   280,   281,
     282,   279,   277,   407,     0,   400,   455,   443,   445,   449,
     447,   453,   451,   441,   342,   170,   346,   344,   349,   376,
     209,   211,   522,   524,   527,   532,   533,   531,   535,   541,
     542,   543,   544,   545,   540,   547,     0,    42,     0,     0,
       0,   156,   162,   164,   166,     0,     0,     0,     0,     0,
     175,   177,   155,     0,   141,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,     0,   139,     0,
     136,   137,   234,     0,   231,   232,   320,     0,   317,   318,
     357,     0,   354,   355,   291,     0,   288,   289,   188,   189,
     190,   191,   192,     0,   181,   183,   184,   185,   186,   187,
     464,     0,   462,   199,     0,   196,   197,     0,     0,     0,
       0,     0,     0,     0,   214,   216,   217,   218,   219,   220,
     221,   493,   495,   492,   490,   491,     0,   486,   488,   489,
       0,    51,   387,     0,   384,   385,   411,     0,   408,   409,
     458,     0,   565,     0,   563,    67,   555,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,   132,     0,   134,     0,     0,   229,     0,   324,   313,
       0,   361,   352,     0,     0,   286,     0,     0,   180,   466,
       0,   461,     0,   194,     0,     0,     0,     0,     0,     0,
       0,     0,   213,     0,     0,     0,   485,   498,    53,     0,
      52,     0,   382,     0,   415,   406,     0,     0,   457,     0,
       0,   562,     0,     0,     0,     0,   168,   171,   172,   173,
     174,     0,     0,   142,     0,   138,     0,   233,     0,   319,
       0,   356,   311,   308,   298,   299,   301,   295,   296,   297,
     307,   306,     0,   293,   300,   309,   310,   302,   303,   304,
     305,   290,   182,   481,   479,   480,   472,   473,   477,   478,
     474,   475,   476,     0,   467,   468,   470,   471,   463,     0,
     198,   222,   223,   224,   225,   226,   227,   215,     0,     0,
     487,    50,     0,     0,   386,     0,   410,     0,   579,     0,
     577,   575,   569,   573,   574,     0,   567,   571,   572,   570,
     564,   158,   159,   160,   161,   157,   163,   165,   167,   176,
     178,   140,   235,   321,   358,     0,   292,     0,   465,     0,
     200,   494,   496,    54,   388,   412,   459,     0,     0,     0,
       0,   566,   294,     0,   469,     0,   576,     0,   568,   482,
       0,   578,   583,     0,   581,     0,     0,   580,   591,     0,
       0,     0,     0,   585,   587,   588,   589,   590,   582,     0,
       0,     0,     0,     0,   584,     0,   593,   594,   595,   586,
     592
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,   -37,  -737,   211,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,   184,  -737,  -737,  -737,
     -66,  -737,  -737,  -737,   350,  -737,  -737,  -737,  -737,   148,
     330,   -38,   -26,   -23,  -737,  -737,   -21,  -737,  -737,   147,
     306,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
     -52,  -737,  -535,   -36,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,   -22,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,   -56,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,   -60,  -737,  -737,
    -737,   -50,   288,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
     -69,  -737,  -737,  -737,  -737,  -737,  -737,  -736,  -737,  -737,
    -737,   -11,  -737,  -737,  -737,   -35,   357,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -733,  -737,  -737,  -737,   -20,
    -737,  -722,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
     -17,  -737,  -737,  -155,   -61,  -737,  -737,  -737,  -737,  -737,
      -6,  -737,  -737,  -737,    -2,  -737,   343,  -737,   -68,  -737,
    -737,  -737,  -737,  -737,   -62,  -737,  -737,  -737,  -737,  -737,
      -3,  -737,  -737,  -737,    -8,  -737,  -737,  -737,     1,  -737,
     344,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,   -29,  -737,  -737,  -737,   -16,   380,  -737,  -737,
     -54,  -737,   -34,  -737,  -737,  -737,  -737,  -737,   -18,  -737,
    -737,  -737,   -24,  -737,   364,   -46,  -737,     3,  -737,     4,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -721,  -737,  -737,
    -737,  -737,  -737,  -737,     6,  -737,  -737,  -737,  -129,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,    -4,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,   212,   348,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
    -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,  -737,
     234,   359,  -737,  -737,  -737,   -15,  -737,  -737,  -138,  -737,
    -737,  -737,  -737,  -737,  -737,  -150,  -737,  -737,  -166,  -737,
    -737,  -737,  -737,  -737
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   555,
      82,    83,    39,    64,    79,    80,   564,   711,   779,   780,
     632,    41,    66,    91,    92,    93,   331,    43,    67,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   339,   158,
     159,    45,    68,   160,   367,   161,   368,   567,   162,   369,
     570,   163,   134,   345,   135,   346,   136,   347,   649,   650,
     651,   742,   633,   634,   635,   728,   885,   636,   729,   637,
     730,   638,   731,   639,   640,   403,   641,   642,   643,   644,
     645,   737,   646,   738,   137,   358,   673,   674,   675,   676,
     677,   678,   679,   138,   360,   684,   685,   686,   762,    59,
      75,   285,   286,   287,   416,   288,   417,   139,   361,   693,
     694,   695,   696,   697,   698,   699,   700,   140,   352,   653,
     654,   655,   745,    47,    69,   184,   185,   186,   377,   187,
     373,   188,   374,   189,   375,   190,   378,   191,   379,   192,
     383,   193,   382,   581,   194,   195,   141,   355,   665,   666,
     667,   754,   822,   823,   142,   353,    53,    72,   657,   658,
     659,   748,    55,    73,   250,   251,   252,   253,   254,   255,
     256,   402,   257,   406,   258,   405,   259,   260,   407,   261,
     143,   354,   661,   662,   663,   751,    57,    74,   271,   272,
     273,   274,   275,   411,   276,   277,   278,   279,   197,   376,
     713,   714,   715,   781,    49,    70,   209,   210,   211,   388,
     144,   356,   145,   357,   200,   384,   717,   718,   719,   784,
      51,    71,   226,   227,   228,   146,   342,   147,   343,   148,
     344,   232,   398,   233,   392,   234,   393,   235,   395,   236,
     394,   237,   397,   238,   396,   239,   391,   204,   385,   721,
     787,   149,   359,   681,   682,   759,   843,   844,   845,   846,
     847,   897,   150,   151,   363,   706,   707,   708,   773,   709,
     774,   152,   364,    61,    76,   306,   307,   308,   309,   421,
     310,   422,   311,   312,   424,   313,   314,   315,   427,   607,
     316,   428,   317,   318,   319,   320,   432,   614,   321,   433,
      94,   333,    95,   334,    96,   335,    97,   332,    63,    77,
     323,   324,   325,   436,   723,   724,   789,   875,   876,   877,
     878,   909,   879,   907,   923,   924,   925,   932,   933,   934,
     939,   935,   936,   937
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   124,   157,   179,   206,   222,   269,   248,   267,   284,
     303,   240,   270,   647,   164,   198,   212,   224,   818,   262,
     280,   819,   304,   201,    29,   229,    30,    78,    31,   565,
     566,   180,   821,   830,   165,   199,   213,   225,   605,   263,
     281,    84,   305,   181,    98,    28,   182,    40,   183,    81,
     207,   249,   268,    99,   100,   101,   102,   103,   104,   105,
     106,   578,   579,   580,   337,   365,   196,   208,   223,   338,
     366,    42,   202,   203,   230,   231,   107,   108,   109,   110,
     111,   282,   283,   371,   112,   113,   153,   154,   372,    44,
     155,   115,   116,   156,   113,   114,   568,   569,   115,   116,
     101,   102,   103,   242,   282,   283,   205,   115,   116,   117,
     118,    46,    48,    50,   928,   115,   116,   929,   930,   931,
     241,   176,   119,   757,    52,   120,   758,   701,   702,   112,
     113,   242,   121,   122,    54,   760,   123,   386,   761,   115,
     116,   606,   387,   115,   116,   242,    56,   243,   244,   389,
      58,   245,   246,   247,   390,    85,   833,   115,   116,   818,
      60,    62,   819,    89,    86,    87,    88,   418,    32,    33,
      34,    35,   419,   821,   830,    89,   868,   112,   869,   870,
      89,   790,    89,   322,   791,   434,   100,   101,   102,   103,
     435,    89,   326,   437,   327,   101,   102,   103,   438,    89,
     687,   688,   689,   690,   691,   692,   365,   804,   107,   108,
     109,   725,   328,   166,   167,   168,   330,   113,   329,   609,
     610,   611,   612,    89,   437,   113,   336,    89,   169,   726,
     115,   116,   170,   171,   172,   173,   174,   175,   115,   116,
     340,    89,   371,   739,   176,   177,   926,   727,   740,   927,
     214,   613,   178,   341,   215,   216,   217,   218,   219,   220,
     348,   221,   668,   669,   670,   671,   349,   672,   739,   771,
     621,    90,   350,   741,   772,   622,   623,   624,   625,   626,
     627,   628,   629,   630,   631,   351,   362,   775,   434,   739,
     439,   440,   776,   777,   891,   242,   386,   895,   418,   124,
     370,   892,   896,   900,   380,   157,   242,   264,   243,   244,
     265,   266,   381,   399,    89,   400,   441,   164,   115,   116,
     179,   389,    89,   206,   910,   943,   904,   401,   404,   911,
     944,   408,   198,   409,   222,   212,   410,   165,   412,   413,
     201,   415,   457,   420,   248,   414,   224,   269,   180,   267,
     423,   425,   199,   270,   229,   213,   262,   426,   429,   430,
     181,   280,   431,   182,   442,   183,   225,   443,   303,   207,
     881,   882,   883,   884,   444,   445,   263,   446,   115,   116,
     304,   281,   448,   196,   449,   450,   208,   451,   249,   202,
     203,    89,   452,   268,   453,   454,   455,   223,   456,   461,
     305,   458,    89,   230,   231,   459,   462,   540,   541,   542,
     100,   101,   102,   103,   460,   463,   464,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   465,   107,   108,   109,   466,   111,   467,   468,   469,
     470,   113,   242,   472,   473,   475,   476,   471,   477,   480,
     478,   481,   482,   483,   115,   116,   484,   171,   485,   486,
     487,   175,    89,   488,   489,   490,   491,   492,   176,   494,
     496,   497,   124,   498,   499,   500,   178,   157,   501,   502,
     503,   601,   505,   506,   508,   509,   507,   510,   513,   164,
     517,   518,   511,   521,   514,   703,   303,   515,   522,   524,
     617,   520,   523,   527,   528,   532,   525,   704,   304,   165,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   533,   529,   526,   535,   705,   305,   530,
     537,   531,   538,   544,   539,   543,   545,   547,    89,   548,
     549,   550,   546,   551,   552,   553,   556,   557,    30,   558,
     559,   788,   571,   560,   561,   562,   563,   572,   573,   574,
     583,   616,   575,   576,   577,   582,   584,   585,   587,   588,
     589,   590,   591,   592,   593,   594,   608,   595,   596,   597,
     648,   598,   652,   656,   660,   664,   599,   600,   680,   683,
     712,   716,   602,   720,   722,   603,   732,   733,   734,   604,
     615,   735,   736,   744,   893,   743,   747,   746,   749,   750,
     752,   753,   756,   755,   764,   783,   763,   765,   766,   767,
     768,   769,   770,   786,   797,   782,   778,   785,   792,   793,
     794,   795,   796,   801,   802,   798,   858,   859,   862,   886,
     799,   800,   851,   852,   861,   867,   853,   854,   855,   899,
     894,   898,   856,   887,   908,   888,   889,   890,   901,   902,
     903,   905,   906,   913,   915,   916,   917,   919,   920,   921,
     940,   922,   941,   942,   945,   946,   554,   479,   950,   179,
     586,   947,   248,   269,   948,   267,   618,   447,   812,   270,
     620,   198,   805,   834,   262,   474,   284,   280,   836,   201,
     825,   832,   857,   803,   850,   838,   519,   180,   827,   703,
     806,   199,   849,   840,   263,   206,   813,   281,   222,   181,
     826,   704,   182,   871,   183,   839,   249,   212,   814,   268,
     224,   815,   817,   816,   820,   873,   807,   835,   229,   831,
     912,   705,   196,   493,   809,   811,   808,   213,   202,   203,
     225,   824,   810,   512,   864,   874,   837,   828,   829,   516,
     865,   207,   841,   842,   504,   863,   848,   872,   866,   495,
     914,   860,   918,   619,   710,   880,   938,   949,   208,     0,
       0,   223,   534,     0,     0,     0,     0,   230,   231,     0,
       0,     0,     0,     0,     0,     0,   536,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   812,
       0,     0,     0,   834,     0,     0,     0,     0,   836,     0,
       0,   825,     0,     0,   871,   838,     0,     0,     0,   827,
       0,     0,     0,   840,     0,     0,   873,   813,     0,     0,
       0,   826,     0,     0,     0,   839,     0,     0,     0,   814,
       0,     0,   815,   817,   816,   820,   874,   835,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   872,     0,
       0,     0,   824,     0,     0,     0,   837,     0,   828,   829,
       0,     0,   841,   842
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    67,    68,    69,    70,    71,    74,    73,    74,    75,
      76,    72,    74,   548,    68,    69,    70,    71,   754,    73,
      74,   754,    76,    69,     5,    71,     7,    64,     9,    14,
      15,    69,   754,   754,    68,    69,    70,    71,    15,    73,
      74,    10,    76,    69,    11,     0,    69,     7,    69,   149,
      70,    73,    74,    20,    21,    22,    23,    24,    25,    26,
      27,    73,    74,    75,     3,     3,    69,    70,    71,     8,
       8,     7,    69,    69,    71,    71,    43,    44,    45,    46,
      47,    90,    91,     3,    51,    52,    12,    13,     8,     7,
      16,    65,    66,    19,    52,    62,    17,    18,    65,    66,
      22,    23,    24,    53,    90,    91,    64,    65,    66,    76,
      77,     7,     7,     7,   127,    65,    66,   130,   131,   132,
      28,    79,    89,     3,     7,    92,     6,   101,   102,    51,
      52,    53,    99,   100,     7,     3,   103,     3,     6,    65,
      66,   118,     8,    65,    66,    53,     7,    55,    56,     3,
       7,    59,    60,    61,     8,   124,    78,    65,    66,   895,
       7,     7,   895,   149,   133,   134,   135,     3,   149,   150,
     151,   152,     8,   895,   895,   149,   126,    51,   128,   129,
     149,     3,   149,   125,     6,     3,    21,    22,    23,    24,
       8,   149,     6,     3,     3,    22,    23,    24,     8,   149,
      93,    94,    95,    96,    97,    98,     3,   742,    43,    44,
      45,     8,     4,    48,    49,    50,     3,    52,     8,   120,
     121,   122,   123,   149,     3,    52,     4,   149,    63,     8,
      65,    66,    67,    68,    69,    70,    71,    72,    65,    66,
       4,   149,     3,     3,    79,    80,     3,     8,     8,     6,
      77,   152,    87,     4,    81,    82,    83,    84,    85,    86,
       4,    88,    81,    82,    83,    84,     4,    86,     3,     3,
      28,   337,     4,     8,     8,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     4,     4,     3,     3,     3,
     327,   328,     8,     8,     8,    53,     3,     3,     3,   365,
       4,     8,     8,     8,     4,   371,    53,    54,    55,    56,
      57,    58,     4,     8,   149,     3,   149,   371,    65,    66,
     386,     3,   149,   389,     3,     3,     8,     8,     4,     8,
       8,     4,   386,     8,   400,   389,     3,   371,     4,     4,
     386,     3,   150,     4,   410,     8,   400,   415,   386,   415,
       4,     4,   386,   415,   400,   389,   410,     4,     4,     4,
     386,   415,     4,   386,     4,   386,   400,     4,   434,   389,
      29,    30,    31,    32,     4,     4,   410,     4,    65,    66,
     434,   415,     4,   386,   152,   152,   389,     4,   410,   386,
     386,   149,     4,   415,     4,     4,     4,   400,     4,     4,
     434,   150,   149,   400,   400,   150,     4,   444,   445,   446,
      21,    22,    23,    24,   150,     4,     4,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,     4,    43,    44,    45,     4,    47,     4,     4,     4,
       4,    52,    53,     4,     4,     4,     4,   150,     4,     4,
     152,     4,     4,     4,    65,    66,     4,    68,     4,     4,
     150,    72,   149,   152,     4,     4,     4,     4,    79,     4,
       4,     4,   538,     4,     4,     4,    87,   543,     4,     4,
       4,   518,     4,     4,     4,     4,   150,     4,     4,   543,
       4,     4,   152,     4,   152,   561,   562,   152,     4,     4,
     537,   152,   150,     4,     4,     4,   150,   561,   562,   543,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,     4,   152,   150,     4,   561,   562,   152,
       4,   152,     7,   149,     7,     7,   149,     7,   149,     7,
       5,     5,   149,     5,     5,     5,   149,     5,     7,     5,
       5,     8,   149,     7,     7,     7,     5,   149,   149,     5,
       5,     5,   149,   149,   149,   149,     7,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   119,   149,   149,   149,
       7,   149,     7,     7,     7,     7,   149,   149,     7,     7,
       7,     7,   149,    88,     7,   149,     4,     4,     4,   149,
     149,     4,     4,     3,     8,     6,     3,     6,     6,     3,
       6,     3,     3,     6,     3,     3,     6,     4,     4,     4,
       4,     4,     4,     3,   152,     6,   149,     6,     4,     4,
       4,     4,   150,     4,     4,   150,     4,     4,     3,   149,
     152,   150,   150,   150,     6,     4,   150,   150,   150,     3,
       8,     8,   150,   149,     4,   149,   149,   149,   149,   149,
     149,     8,   149,     4,     4,   150,     4,   149,     5,   149,
       4,     7,     4,     4,     4,   152,   465,   371,   149,   745,
     496,   150,   748,   751,   150,   751,   538,   337,   754,   751,
     543,   745,   744,   759,   748,   365,   762,   751,   759,   745,
     754,   757,   771,   739,   764,   759,   418,   745,   754,   775,
     745,   745,   762,   759,   748,   781,   754,   751,   784,   745,
     754,   775,   745,   789,   745,   759,   748,   781,   754,   751,
     784,   754,   754,   754,   754,   789,   747,   759,   784,   756,
     895,   775,   745,   386,   750,   753,   748,   781,   745,   745,
     784,   754,   751,   410,   783,   789,   759,   754,   754,   415,
     784,   781,   759,   759,   400,   781,   760,   789,   786,   389,
     899,   775,   910,   539,   562,   790,   926,   943,   781,    -1,
      -1,   784,   434,    -1,    -1,    -1,    -1,   784,   784,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   437,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   895,
      -1,    -1,    -1,   899,    -1,    -1,    -1,    -1,   899,    -1,
      -1,   895,    -1,    -1,   910,   899,    -1,    -1,    -1,   895,
      -1,    -1,    -1,   899,    -1,    -1,   910,   895,    -1,    -1,
      -1,   895,    -1,    -1,    -1,   899,    -1,    -1,    -1,   895,
      -1,    -1,   895,   895,   895,   895,   910,   899,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   910,    -1,
      -1,    -1,   895,    -1,    -1,    -1,   899,    -1,   895,   895,
      -1,    -1,   899,   899
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,     0,     5,
       7,     9,   149,   150,   151,   152,   168,   169,   170,   175,
       7,   184,     7,   190,     7,   204,     7,   286,     7,   367,
       7,   383,     7,   319,     7,   325,     7,   349,     7,   262,
       7,   436,     7,   471,   176,   171,   185,   191,   205,   287,
     368,   384,   320,   326,   350,   263,   437,   472,   168,   177,
     178,   149,   173,   174,    10,   124,   133,   134,   135,   149,
     183,   186,   187,   188,   463,   465,   467,   469,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    43,    44,    45,
      46,    47,    51,    52,    62,    65,    66,    76,    77,    89,
      92,    99,   100,   103,   183,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   215,   217,   219,   247,   256,   270,
     280,   309,   317,   343,   373,   375,   388,   390,   392,   414,
     425,   426,   434,    12,    13,    16,    19,   183,   202,   203,
     206,   208,   211,   214,   373,   375,    48,    49,    50,    63,
      67,    68,    69,    70,    71,    72,    79,    80,    87,   183,
     194,   195,   196,   199,   288,   289,   290,   292,   294,   296,
     298,   300,   302,   304,   307,   308,   343,   361,   373,   375,
     377,   388,   390,   392,   410,    64,   183,   302,   343,   369,
     370,   371,   373,   375,    77,    81,    82,    83,    84,    85,
      86,    88,   183,   343,   373,   375,   385,   386,   387,   388,
     390,   392,   394,   396,   398,   400,   402,   404,   406,   408,
     317,    28,    53,    55,    56,    59,    60,    61,   183,   237,
     327,   328,   329,   330,   331,   332,   333,   335,   337,   339,
     340,   342,   373,   375,    54,    57,    58,   183,   237,   331,
     337,   351,   352,   353,   354,   355,   357,   358,   359,   360,
     373,   375,    90,    91,   183,   264,   265,   266,   268,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   183,   373,   375,   438,   439,   440,   441,
     443,   445,   446,   448,   449,   450,   453,   455,   456,   457,
     458,   461,   125,   473,   474,   475,     6,     3,     4,     8,
       3,   189,   470,   464,   466,   468,     4,     3,     8,   201,
       4,     4,   389,   391,   393,   216,   218,   220,     4,     4,
       4,     4,   281,   318,   344,   310,   374,   376,   248,   415,
     257,   271,     4,   427,   435,     3,     8,   207,   209,   212,
       4,     3,     8,   293,   295,   297,   362,   291,   299,   301,
       4,     4,   305,   303,   378,   411,     3,     8,   372,     3,
       8,   409,   397,   399,   403,   401,   407,   405,   395,     8,
       3,     8,   334,   238,     4,   338,   336,   341,     4,     8,
       3,   356,     4,     4,     8,     3,   267,   269,     3,     8,
       4,   442,   444,     4,   447,     4,     4,   451,   454,     4,
       4,     4,   459,   462,     3,     8,   476,     3,     8,   168,
     168,   149,     4,     4,     4,     4,     4,   187,     4,   152,
     152,     4,     4,     4,     4,     4,     4,   150,   150,   150,
     150,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   150,     4,     4,   193,     4,     4,     4,   152,   203,
       4,     4,     4,     4,     4,     4,     4,   150,   152,     4,
       4,     4,     4,   289,     4,   370,     4,     4,     4,     4,
       4,     4,     4,     4,   387,     4,     4,   150,     4,     4,
       4,   152,   329,     4,   152,   152,   353,     4,     4,   265,
     152,     4,     4,   150,     4,   150,   150,     4,     4,   152,
     152,   152,     4,     4,   439,     4,   474,     4,     7,     7,
     168,   168,   168,     7,   149,   149,   149,     7,     7,     5,
       5,     5,     5,     5,   170,   172,   149,     5,     5,     5,
       7,     7,     7,     5,   179,    14,    15,   210,    17,    18,
     213,   149,   149,   149,     5,   149,   149,   149,    73,    74,
      75,   306,   149,     5,     7,   149,   179,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   168,   149,   149,   149,    15,   118,   452,   119,   120,
     121,   122,   123,   152,   460,   149,     5,   168,   192,   473,
     202,    28,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,   183,   225,   226,   227,   230,   232,   234,   236,
     237,   239,   240,   241,   242,   243,   245,   225,     7,   221,
     222,   223,     7,   282,   283,   284,     7,   321,   322,   323,
       7,   345,   346,   347,     7,   311,   312,   313,    81,    82,
      83,    84,    86,   249,   250,   251,   252,   253,   254,   255,
       7,   416,   417,     7,   258,   259,   260,    93,    94,    95,
      96,    97,    98,   272,   273,   274,   275,   276,   277,   278,
     279,   101,   102,   183,   373,   375,   428,   429,   430,   432,
     438,   180,     7,   363,   364,   365,     7,   379,   380,   381,
      88,   412,     7,   477,   478,     8,     8,     8,   228,   231,
     233,   235,     4,     4,     4,     4,     4,   244,   246,     3,
       8,     8,   224,     6,     3,   285,     6,     3,   324,     6,
       3,   348,     6,     3,   314,     6,     3,     3,     6,   418,
       3,     6,   261,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   431,   433,     3,     8,     8,   149,   181,
     182,   366,     6,     3,   382,     6,     3,   413,     8,   479,
       3,     6,     4,     4,     4,     4,   150,   152,   150,   152,
     150,     4,     4,   226,   225,   223,   288,   284,   327,   323,
     351,   347,   183,   194,   195,   196,   199,   237,   280,   298,
     302,   304,   315,   316,   343,   373,   375,   388,   390,   392,
     410,   313,   250,    78,   183,   237,   317,   343,   373,   375,
     388,   390,   392,   419,   420,   421,   422,   423,   417,   264,
     260,   150,   150,   150,   150,   150,   150,   273,     4,     4,
     429,     6,     3,   369,   365,   385,   381,     4,   126,   128,
     129,   183,   237,   373,   375,   480,   481,   482,   483,   485,
     478,    29,    30,    31,    32,   229,   149,   149,   149,   149,
     149,     8,     8,     8,     8,     3,     8,   424,     8,     3,
       8,   149,   149,   149,     8,     8,   149,   486,     4,   484,
       3,     8,   316,     4,   421,     4,   150,     4,   481,   149,
       5,   149,     7,   487,   488,   489,     3,     6,   127,   130,
     131,   132,   490,   491,   492,   494,   495,   496,   488,   493,
       4,     4,     4,     3,     8,     4,   152,   150,   150,   491,
     149
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   153,   155,   154,   156,   154,   157,   154,   158,   154,
     159,   154,   160,   154,   161,   154,   162,   154,   163,   154,
     164,   154,   165,   154,   166,   154,   167,   154,   168,   168,
     168,   168,   168,   168,   168,   169,   171,   170,   172,   173,
     173,   174,   174,   176,   175,   177,   177,   178,   178,   180,
     179,   181,   181,   182,   182,   183,   185,   184,   186,   186,
     187,   187,   187,   187,   187,   187,   189,   188,   191,   190,
     192,   192,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   194,
     195,   196,   197,   198,   199,   201,   200,   202,   202,   203,
     203,   203,   203,   203,   203,   203,   205,   204,   207,   206,
     209,   208,   210,   210,   212,   211,   213,   213,   214,   216,
     215,   218,   217,   220,   219,   221,   221,   222,   222,   224,
     223,   225,   225,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   228,   227,   229,   229,
     229,   229,   231,   230,   233,   232,   235,   234,   236,   238,
     237,   239,   240,   241,   242,   244,   243,   246,   245,   248,
     247,   249,   249,   250,   250,   250,   250,   250,   251,   252,
     253,   254,   255,   257,   256,   258,   258,   259,   259,   261,
     260,   263,   262,   264,   264,   264,   265,   265,   267,   266,
     269,   268,   271,   270,   272,   272,   273,   273,   273,   273,
     273,   273,   274,   275,   276,   277,   278,   279,   281,   280,
     282,   282,   283,   283,   285,   284,   287,   286,   288,   288,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   291,   290,   293,   292,   295,   294,
     297,   296,   299,   298,   301,   300,   303,   302,   305,   304,
     306,   306,   306,   307,   308,   310,   309,   311,   311,   312,
     312,   314,   313,   315,   315,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   318,   317,   320,   319,   321,   321,   322,   322,
     324,   323,   326,   325,   327,   327,   328,   328,   329,   329,
     329,   329,   329,   329,   329,   329,   329,   329,   330,   331,
     332,   334,   333,   336,   335,   338,   337,   339,   341,   340,
     342,   344,   343,   345,   345,   346,   346,   348,   347,   350,
     349,   351,   351,   352,   352,   353,   353,   353,   353,   353,
     353,   353,   353,   353,   354,   356,   355,   357,   358,   359,
     360,   362,   361,   363,   363,   364,   364,   366,   365,   368,
     367,   369,   369,   370,   370,   370,   370,   370,   370,   372,
     371,   374,   373,   376,   375,   378,   377,   379,   379,   380,
     380,   382,   381,   384,   383,   385,   385,   386,   386,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   389,   388,   391,   390,   393,   392,
     395,   394,   397,   396,   399,   398,   401,   400,   403,   402,
     405,   404,   407,   406,   409,   408,   411,   410,   413,   412,
     415,   414,   416,   416,   418,   417,   419,   419,   420,   420,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     422,   424,   423,   425,   427,   426,   428,   428,   429,   429,
     429,   429,   429,   431,   430,   433,   432,   435,   434,   437,
     436,   438,   438,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     440,   442,   441,   444,   443,   445,   447,   446,   448,   449,
     451,   450,   452,   452,   454,   453,   455,   456,   457,   459,
     458,   460,   460,   460,   460,   460,   462,   461,   464,   463,
     466,   465,   468,   467,   470,   469,   472,   471,   473,   473,
     474,   476,   475,   477,   477,   479,   478,   480,   480,   481,
     481,   481,   481,   481,   481,   481,   482,   484,   483,   486,
     485,   487,   487,   489,   488,   490,   490,   491,   491,   491,
     491,   493,   492,   494,   495,   496
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
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
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
  "hosts_databases", "$@27", "database_list", "not_empty_database_list",
  "database", "$@28", "database_map_params", "database_map_param",
  "database_type", "$@29", "db_type", "user", "$@30", "password", "$@31",
  "host", "$@32", "port", "name", "$@33", "persist", "lfc_interval",
  "readonly", "connect_timeout", "contact_points", "$@34", "keyspace",
  "$@35", "host_reservation_identifiers", "$@36",
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
  "$@51", "client_class", "$@52", "reservation_mode", "$@53", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@54",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@55", "shared_network_params", "shared_network_param",
  "option_def_list", "$@56", "sub_option_def_list", "$@57",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@58", "sub_option_def", "$@59",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@60",
  "option_def_record_types", "$@61", "space", "$@62", "option_def_space",
  "option_def_encapsulate", "$@63", "option_def_array", "option_data_list",
  "$@64", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@65", "sub_option_data", "$@66",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@67",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@68", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@69", "sub_pool4", "$@70",
  "pool_params", "pool_param", "pool_entry", "$@71", "user_context",
  "$@72", "comment", "$@73", "reservations", "$@74", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@75", "sub_reservation",
  "$@76", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@77", "server_hostname", "$@78",
  "boot_file_name", "$@79", "ip_address", "$@80", "duid", "$@81",
  "hw_address", "$@82", "client_id_value", "$@83", "circuit_id_value",
  "$@84", "flex_id_value", "$@85", "hostname", "$@86",
  "reservation_client_classes", "$@87", "relay", "$@88", "relay_map",
  "$@89", "client_classes", "$@90", "client_classes_list",
  "client_class_entry", "$@91", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@92", "dhcp4o6_port",
  "control_socket", "$@93", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@94",
  "control_socket_name", "$@95", "dhcp_ddns", "$@96", "sub_dhcp_ddns",
  "$@97", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@98", "server_ip", "$@99", "server_port",
  "sender_ip", "$@100", "sender_port", "max_queue_size", "ncr_protocol",
  "$@101", "ncr_protocol_value", "ncr_format", "$@102",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@103", "replace_client_name_value",
  "generated_prefix", "$@104", "dhcp6_json_object", "$@105",
  "dhcpddns_json_object", "$@106", "control_agent_json_object", "$@107",
  "logging_object", "$@108", "sub_logging", "$@109", "logging_params",
  "logging_param", "loggers", "$@110", "loggers_entries", "logger_entry",
  "$@111", "logger_params", "logger_param", "debuglevel", "severity",
  "$@112", "output_options_list", "$@113", "output_options_list_content",
  "output_entry", "$@114", "output_params_list", "output_params", "output",
  "$@115", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   236,   236,   236,   237,   237,   238,   238,   239,   239,
     240,   240,   241,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   247,   248,   248,   256,   257,
     258,   259,   260,   261,   262,   265,   270,   270,   281,   284,
     285,   288,   292,   299,   299,   306,   307,   310,   314,   321,
     321,   328,   329,   332,   336,   347,   357,   357,   373,   374,
     378,   379,   380,   381,   382,   383,   386,   386,   401,   401,
     410,   411,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   445,
     450,   455,   460,   465,   470,   476,   476,   487,   488,   491,
     492,   493,   494,   495,   496,   497,   500,   500,   509,   509,
     519,   519,   526,   527,   530,   530,   537,   539,   543,   549,
     549,   561,   561,   573,   573,   583,   584,   587,   588,   591,
     591,   601,   602,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   620,   620,   627,   628,
     629,   630,   633,   633,   641,   641,   649,   649,   657,   662,
     662,   670,   675,   680,   685,   690,   690,   698,   698,   707,
     707,   717,   718,   721,   722,   723,   724,   725,   728,   733,
     738,   743,   748,   753,   753,   763,   764,   767,   768,   771,
     771,   781,   781,   791,   792,   793,   796,   797,   800,   800,
     808,   808,   816,   816,   827,   828,   831,   832,   833,   834,
     835,   836,   839,   844,   849,   854,   859,   864,   872,   872,
     885,   886,   889,   890,   897,   897,   923,   923,   934,   935,
     939,   940,   941,   942,   943,   944,   945,   946,   947,   948,
     949,   950,   951,   952,   953,   954,   955,   956,   957,   958,
     959,   960,   961,   962,   965,   965,   973,   973,   981,   981,
     989,   989,   997,   997,  1005,  1005,  1013,  1013,  1021,  1021,
    1028,  1029,  1030,  1033,  1038,  1045,  1045,  1056,  1057,  1061,
    1062,  1065,  1065,  1073,  1074,  1077,  1078,  1079,  1080,  1081,
    1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,
    1092,  1093,  1100,  1100,  1113,  1113,  1122,  1123,  1126,  1127,
    1132,  1132,  1147,  1147,  1161,  1162,  1165,  1166,  1169,  1170,
    1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1181,  1183,
    1188,  1190,  1190,  1198,  1198,  1206,  1206,  1214,  1216,  1216,
    1224,  1233,  1233,  1245,  1246,  1251,  1252,  1257,  1257,  1269,
    1269,  1281,  1282,  1287,  1288,  1293,  1294,  1295,  1296,  1297,
    1298,  1299,  1300,  1301,  1304,  1306,  1306,  1314,  1316,  1318,
    1323,  1331,  1331,  1343,  1344,  1347,  1348,  1351,  1351,  1361,
    1361,  1371,  1372,  1375,  1376,  1377,  1378,  1379,  1380,  1383,
    1383,  1391,  1391,  1416,  1416,  1446,  1446,  1456,  1457,  1460,
    1461,  1464,  1464,  1473,  1473,  1482,  1483,  1486,  1487,  1491,
    1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,
    1502,  1503,  1504,  1505,  1508,  1508,  1516,  1516,  1524,  1524,
    1532,  1532,  1540,  1540,  1548,  1548,  1556,  1556,  1564,  1564,
    1572,  1572,  1580,  1580,  1588,  1588,  1601,  1601,  1611,  1611,
    1622,  1622,  1632,  1633,  1636,  1636,  1646,  1647,  1650,  1651,
    1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,
    1666,  1668,  1668,  1680,  1687,  1687,  1697,  1698,  1701,  1702,
    1703,  1704,  1705,  1708,  1708,  1716,  1716,  1726,  1726,  1738,
    1738,  1748,  1749,  1752,  1753,  1754,  1755,  1756,  1757,  1758,
    1759,  1760,  1761,  1762,  1763,  1764,  1765,  1766,  1767,  1768,
    1771,  1776,  1776,  1784,  1784,  1792,  1797,  1797,  1805,  1810,
    1815,  1815,  1823,  1824,  1827,  1827,  1835,  1840,  1845,  1850,
    1850,  1858,  1861,  1864,  1867,  1870,  1876,  1876,  1886,  1886,
    1893,  1893,  1900,  1900,  1912,  1912,  1922,  1922,  1933,  1934,
    1938,  1942,  1942,  1954,  1955,  1959,  1959,  1967,  1968,  1971,
    1972,  1973,  1974,  1975,  1976,  1977,  1980,  1985,  1985,  1993,
    1993,  2003,  2004,  2007,  2007,  2015,  2016,  2019,  2020,  2021,
    2022,  2025,  2025,  2033,  2038,  2043
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
#line 4550 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2048 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
