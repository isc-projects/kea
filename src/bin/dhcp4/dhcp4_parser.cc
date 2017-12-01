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
      case 165: // value
      case 169: // map_value
      case 207: // socket_type
      case 210: // outbound_interface_value
      case 220: // db_type
      case 297: // hr_mode
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 165: // value
      case 169: // map_value
      case 207: // socket_type
      case 210: // outbound_interface_value
      case 220: // db_type
      case 297: // hr_mode
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
            case 147: // "constant string"

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 148: // "integer"

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 149: // "floating point"

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 150: // "boolean"

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 165: // value

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 169: // map_value

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 207: // socket_type

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 210: // outbound_interface_value

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 220: // db_type

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 297: // hr_mode

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 442: // ncr_protocol_value

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 450: // replace_client_name_value

#line 225 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 165: // value
      case 169: // map_value
      case 207: // socket_type
      case 210: // outbound_interface_value
      case 220: // db_type
      case 297: // hr_mode
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
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 285 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 296 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 307 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 329 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 344 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 958 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 869 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 873 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 229:
#line 895 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1017 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 284:
#line 1037 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1041 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1088 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1104 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1205 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1210 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
    e->set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.stack_.back()->combine_set("user-context", e);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1412 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2504 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2845 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1790 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1796 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3250 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3254 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -728;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     310,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,    44,    13,    43,    78,    82,    91,   104,
     141,   143,   151,   158,   162,   165,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
      13,    29,     9,   172,    26,    52,   177,   203,   130,    28,
     369,   122,   474,  -728,   178,   179,   184,   183,   207,  -728,
    -728,  -728,  -728,  -728,   209,  -728,    25,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,   217,   251,  -728,  -728,  -728,  -728,
    -728,   258,   276,   277,   278,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,   285,  -728,  -728,  -728,    53,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,   287,
    -728,    59,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,   288,   289,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,    62,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,    69,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,   223,
     242,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,   290,  -728,  -728,   293,  -728,  -728,  -728,
     296,  -728,  -728,   295,   309,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,   316,   318,
    -728,  -728,  -728,  -728,   317,   325,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,    76,  -728,
    -728,  -728,  -728,  -728,   327,  -728,  -728,   328,  -728,   330,
     331,  -728,  -728,   332,   334,   342,  -728,  -728,  -728,  -728,
    -728,    94,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,    13,    13,
    -728,   206,   350,   351,   353,   354,   356,  -728,     9,  -728,
     361,   218,   222,   370,   371,   378,   382,   383,   228,   245,
     246,   248,   385,   386,   393,   394,   400,   401,   423,   424,
     426,   428,   291,   431,   432,   172,  -728,   433,   434,   436,
     292,    26,  -728,   155,   437,   453,   454,   455,   456,   457,
     458,   315,   314,   461,   462,   463,   464,    52,  -728,   465,
     177,  -728,   466,   467,   468,   469,   470,   471,   472,   473,
    -728,   203,  -728,   475,   476,   335,   478,   480,   483,   338,
    -728,    28,   487,   343,   344,  -728,   369,   488,   491,   122,
    -728,   347,   494,   496,   358,   497,   363,   364,   498,   500,
     359,   365,   367,   514,   515,   474,  -728,  -728,  -728,   516,
     517,   520,    13,    13,    13,  -728,   521,  -728,  -728,   376,
     384,   387,   526,   528,  -728,  -728,  -728,  -728,   531,   532,
     535,   536,   537,    13,   540,   541,   542,   543,  -728,   544,
     545,  -728,   548,    49,   247,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,   534,   546,  -728,
    -728,  -728,   408,   409,   410,   553,   412,   413,   414,  -728,
    -728,   128,   415,   558,   557,  -728,   419,  -728,   548,   420,
     421,   422,   425,   427,   444,   445,  -728,   446,   447,  -728,
     448,   449,   450,  -728,  -728,   451,  -728,  -728,  -728,   452,
      13,  -728,  -728,   459,   460,  -728,   477,  -728,  -728,    -2,
     360,  -728,  -728,  -728,   -15,   479,  -728,    13,   172,   481,
    -728,  -728,  -728,    26,  -728,  -728,  -728,   379,   379,   563,
     564,   568,   593,  -728,  -728,  -728,   176,    50,   594,   214,
     152,   474,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
     598,  -728,   155,  -728,  -728,  -728,   596,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,   597,   522,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,   105,
    -728,   126,  -728,  -728,   149,  -728,  -728,  -728,  -728,   604,
     606,   607,   608,   609,  -728,  -728,  -728,   156,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,   163,  -728,   610,   611,  -728,  -728,   612,
     614,  -728,  -728,   613,   617,  -728,  -728,   616,   620,  -728,
    -728,  -728,  -728,  -728,  -728,    75,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,   106,  -728,   619,   624,  -728,   625,   626,
     627,   628,   629,   630,   182,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,   200,  -728,  -728,  -728,   221,   489,
     490,  -728,  -728,   622,   632,  -728,  -728,   633,   635,  -728,
    -728,   634,  -728,   636,   481,  -728,  -728,   637,   639,   640,
     641,   499,   398,   501,   502,   503,   642,   644,   379,  -728,
    -728,    52,  -728,   563,    28,  -728,   564,   369,  -728,   568,
     103,  -728,   593,   176,  -728,    50,  -728,   122,  -728,   594,
     505,   506,   507,   508,   509,   510,   214,  -728,   646,   655,
     152,  -728,  -728,  -728,   654,   658,  -728,   177,  -728,   596,
     203,  -728,   597,   659,  -728,   657,  -728,   372,   518,   519,
     523,  -728,  -728,  -728,  -728,  -728,   524,   525,  -728,   227,
    -728,   656,  -728,   660,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,   231,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,   235,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,   527,   530,  -728,  -728,
     539,   241,  -728,   661,  -728,   547,   666,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
     103,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
     133,  -728,  -728,   252,   666,  -728,  -728,   663,  -728,  -728,
    -728,  -728,  -728,   243,  -728,  -728,  -728,  -728,  -728,   671,
     533,   674,   252,  -728,   679,  -728,   549,  -728,   680,  -728,
    -728,   134,  -728,   146,   680,  -728,  -728,   689,   698,   699,
     270,  -728,  -728,  -728,  -728,  -728,  -728,   701,   559,   560,
     566,   146,  -728,   572,  -728,  -728,  -728,  -728,  -728
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   113,     9,   229,    11,   382,    13,   405,    15,
     307,    17,   315,    19,   352,    21,   192,    23,   488,    25,
      43,    37,     0,     0,     0,     0,     0,   407,     0,   317,
     354,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     543,   537,   539,   541,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   102,     0,     0,   426,   428,   430,   126,
     128,     0,     0,     0,     0,   221,   305,   344,   278,   393,
     395,   170,   452,   184,   205,     0,   476,   486,    95,     0,
      68,    70,    71,    72,    73,    88,    89,    76,    77,    78,
      79,    83,    84,    74,    75,    81,    82,    93,    94,    90,
      91,    92,    80,    85,    86,    87,   115,   117,   121,     0,
     112,     0,   104,   106,   107,   108,   109,   110,   111,   456,
     259,   261,   263,   374,   257,   265,   267,     0,     0,   271,
     269,   397,   448,   256,   233,   234,   235,   247,     0,   231,
     238,   251,   252,   253,   239,   240,   243,   245,   241,   242,
     236,   237,   254,   255,   244,   248,   249,   250,   246,   391,
     390,   387,     0,   384,   386,   388,   389,   446,   434,   436,
     440,   438,   444,   442,   432,   425,   419,   423,   424,     0,
     408,   409,   420,   421,   422,   416,   411,   417,   413,   414,
     415,   418,   412,     0,   334,   160,     0,   338,   336,   341,
       0,   330,   331,     0,   318,   319,   321,   333,   322,   323,
     324,   340,   325,   326,   327,   328,   329,   368,     0,     0,
     366,   367,   370,   371,     0,   355,   356,   358,   359,   360,
     361,   362,   363,   364,   365,   201,   203,   200,     0,   194,
     196,   197,   198,   199,     0,   510,   512,     0,   515,     0,
       0,   519,   523,     0,     0,     0,   528,   535,   508,   506,
     507,     0,   490,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,    42,     0,     0,
      35,     0,     0,     0,     0,     0,     0,    53,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,     0,   114,   458,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,     0,
       0,   383,     0,     0,     0,     0,     0,     0,     0,     0,
     406,     0,   308,     0,     0,     0,     0,     0,     0,     0,
     316,     0,     0,     0,     0,   353,     0,     0,     0,     0,
     193,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   489,    46,    39,     0,
       0,     0,     0,     0,     0,    57,     0,   100,   101,     0,
       0,     0,     0,     0,    96,    97,    98,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   475,     0,
       0,    69,     0,     0,     0,   125,   105,   473,   471,   472,
     464,   465,   469,   470,   466,   467,   468,     0,   459,   460,
     462,   463,     0,     0,     0,     0,     0,     0,     0,   276,
     277,     0,     0,     0,     0,   232,     0,   385,     0,     0,
       0,     0,     0,     0,     0,     0,   410,     0,     0,   332,
       0,     0,     0,   343,   320,     0,   372,   373,   357,     0,
       0,   195,   509,     0,     0,   514,     0,   517,   518,     0,
       0,   525,   526,   527,     0,     0,   491,     0,     0,     0,
     538,   540,   542,     0,   427,   429,   431,     0,     0,   223,
     309,   346,   280,    36,   394,   396,     0,     0,   186,     0,
       0,     0,    47,   116,   119,   120,   118,   123,   124,   122,
       0,   457,     0,   260,   262,   264,   376,   258,   266,   268,
     273,   274,   275,   272,   270,   399,     0,   392,   447,   435,
     437,   441,   439,   445,   443,   433,   335,   161,   339,   337,
     342,   369,   202,   204,   511,   513,   516,   521,   522,   520,
     524,   530,   531,   532,   533,   534,   529,   536,    40,     0,
     548,     0,   545,   547,     0,   147,   153,   155,   157,     0,
       0,     0,     0,     0,   166,   168,   146,     0,   130,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,     0,   227,     0,   224,   225,   313,     0,
     310,   311,   350,     0,   347,   348,   284,     0,   281,   282,
     179,   180,   181,   182,   183,     0,   172,   174,   175,   176,
     177,   178,   454,     0,   190,     0,   187,   188,     0,     0,
       0,     0,     0,     0,     0,   207,   209,   210,   211,   212,
     213,   214,   482,   484,     0,   478,   480,   481,     0,    49,
       0,   461,   380,     0,   377,   378,   403,     0,   400,   401,
     450,     0,    65,     0,     0,   544,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     129,     0,   222,     0,   317,   306,     0,   354,   345,     0,
       0,   279,     0,     0,   171,     0,   453,     0,   185,     0,
       0,     0,     0,     0,     0,     0,     0,   206,     0,     0,
       0,   477,   487,    51,     0,    50,   474,     0,   375,     0,
     407,   398,     0,     0,   449,     0,   546,     0,     0,     0,
       0,   159,   162,   163,   164,   165,     0,     0,   131,     0,
     226,     0,   312,     0,   349,   304,   301,   291,   292,   294,
     288,   289,   290,   300,   299,     0,   286,   293,   302,   303,
     295,   296,   297,   298,   283,   173,   455,     0,   189,   215,
     216,   217,   218,   219,   220,   208,     0,     0,   479,    48,
       0,     0,   379,     0,   402,     0,     0,   149,   150,   151,
     152,   148,   154,   156,   158,   167,   169,   228,   314,   351,
       0,   285,   191,   483,   485,    52,   381,   404,   451,   552,
       0,   550,   287,     0,     0,   549,   566,     0,   564,   562,
     556,   560,   561,     0,   554,   558,   559,   557,   551,     0,
       0,     0,     0,   553,     0,   563,     0,   555,     0,   565,
     570,     0,   568,     0,     0,   567,   578,     0,     0,     0,
       0,   572,   574,   575,   576,   577,   569,     0,     0,     0,
       0,     0,   571,     0,   580,   581,   582,   573,   579
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,   -24,  -728,   259,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,   117,  -728,  -728,  -728,   -62,
    -728,  -728,  -728,   396,  -728,  -728,  -728,  -728,   190,   366,
     -51,   -44,   -28,  -728,  -728,   -25,  -728,  -728,   188,   374,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,   185,     0,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,   -58,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
     -17,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
     -13,  -728,  -728,  -728,   -16,   339,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,   -22,  -728,  -728,  -728,  -728,  -728,  -728,
    -727,  -728,  -728,  -728,     6,  -728,  -728,  -728,    11,   373,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -716,  -728,
    -728,  -728,  -546,  -728,  -709,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,    -5,  -728,  -728,  -107,   -67,  -728,  -728,
    -728,  -728,  -728,    10,  -728,  -728,  -728,    14,  -728,   362,
    -728,   -64,  -728,  -728,  -728,  -728,  -728,   -35,  -728,  -728,
    -728,  -728,  -728,   -50,  -728,  -728,  -728,     8,  -728,  -728,
    -728,    17,  -728,   349,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,   -19,  -728,  -728,  -728,   -12,
     381,  -728,  -728,   -40,  -728,   -18,  -728,  -728,  -728,  -728,
    -728,   -14,  -728,  -728,  -728,   -11,  -728,   375,    -7,  -728,
       1,  -728,     4,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -707,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
     195,  -728,  -728,  -728,  -728,  -728,  -728,  -728,     2,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,   210,   345,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,  -728,
    -728,    51,  -728,  -728,  -728,  -100,  -728,  -728,  -116,  -728,
    -728,  -728,  -728,  -728,  -728,  -127,  -728,  -728,  -143,  -728,
    -728,  -728,  -728,  -728
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   554,    77,
      78,    37,    60,    74,    75,   563,   709,   774,   775,   118,
      39,    62,    86,    87,    88,   322,    41,    63,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   330,   151,   152,
      43,    64,   153,   357,   154,   358,   566,   155,   359,   569,
     156,   128,   336,   129,   337,   637,   638,   639,   727,   851,
     640,   728,   641,   729,   642,   730,   643,   242,   394,   645,
     646,   647,   648,   649,   736,   650,   737,   130,   348,   675,
     676,   677,   678,   679,   680,   681,   131,   350,   685,   686,
     687,   757,    57,    71,   278,   279,   280,   407,   281,   408,
     132,   351,   694,   695,   696,   697,   698,   699,   700,   701,
     133,   342,   655,   656,   657,   741,    45,    65,   178,   179,
     180,   368,   181,   364,   182,   365,   183,   366,   184,   369,
     185,   370,   186,   374,   187,   373,   583,   188,   189,   134,
     345,   667,   668,   669,   750,   815,   816,   135,   343,    51,
      68,   659,   660,   661,   744,    53,    69,   243,   244,   245,
     246,   247,   248,   249,   393,   250,   397,   251,   396,   252,
     253,   398,   254,   136,   344,   663,   664,   665,   747,    55,
      70,   264,   265,   266,   267,   268,   402,   269,   270,   271,
     272,   191,   367,   713,   714,   715,   777,    47,    66,   202,
     203,   204,   379,   137,   346,   138,   347,   194,   375,   717,
     718,   719,   780,    49,    67,   219,   220,   221,   139,   333,
     140,   334,   141,   335,   225,   389,   226,   383,   227,   384,
     228,   386,   229,   385,   230,   388,   231,   387,   232,   382,
     198,   376,   721,   783,   142,   349,   683,   363,   477,   478,
     479,   480,   481,   570,   143,   144,   353,   704,   705,   706,
     768,   707,   769,   145,   354,    59,    72,   301,   302,   303,
     304,   412,   305,   413,   306,   307,   415,   308,   309,   310,
     418,   609,   311,   419,   312,   313,   314,   315,   423,   616,
     316,   424,    89,   324,    90,   325,    91,   326,    92,   323,
     621,   622,   623,   723,   870,   871,   873,   883,   884,   885,
     886,   891,   887,   889,   901,   902,   903,   910,   911,   912,
     917,   913,   914,   915
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   233,   150,   173,   200,   215,   262,   241,   260,   277,
     298,   682,   261,   607,   174,   190,   201,   216,    27,    79,
      28,   175,    29,   811,   157,   192,   205,   217,   328,   255,
     273,   282,   299,   329,   812,   263,    73,   176,   146,   147,
     177,   814,   148,   823,    26,   149,   158,   193,   206,   218,
      38,   256,   274,   283,   300,   234,   355,   159,   195,   159,
     222,   356,   361,   564,   565,   377,   196,   362,   223,   197,
     378,   224,   380,    95,    96,    97,    98,   381,   753,   409,
     235,   754,   236,   237,   410,    40,   238,   239,   240,    42,
     109,   110,   109,   110,   101,   102,   103,   425,    44,   160,
     161,   162,   426,   107,   611,   612,   613,   614,   355,   755,
     159,    46,   756,   722,   163,   608,   109,   110,   164,   165,
     166,   167,   168,   169,    95,    96,    97,    98,   170,   724,
     170,   171,    80,   811,   725,   615,   874,   904,   172,   875,
     905,    81,    82,    83,   812,   101,   102,   103,    48,   105,
      50,   814,   361,   823,   107,   235,    84,   726,    52,   738,
      30,    31,    32,    33,   739,    54,   738,   109,   110,    56,
     165,   740,    58,    84,   169,    84,    76,    96,    97,    98,
     106,   170,   318,    93,   317,   766,   109,   110,   319,   172,
     767,   320,    94,    95,    96,    97,    98,    99,   100,    84,
     580,   581,   582,   770,   813,   106,   107,   235,   771,   826,
     321,   275,   276,   327,   101,   102,   103,   104,   105,   109,
     110,   331,   106,   107,   425,    96,    97,    98,   107,   772,
     377,   390,   467,   108,   860,   857,   109,   110,   409,   861,
     199,   109,   110,   862,   380,   391,   892,   111,   112,   866,
      84,   893,   702,   703,   107,   332,   670,   671,   672,   673,
     113,   674,   338,   114,   567,   568,    85,   109,   110,    84,
     115,   116,   906,   921,   117,   907,   908,   909,   922,   207,
     339,   340,   341,   208,   209,   210,   211,   212,   213,   352,
     214,   360,   371,   372,   427,   428,   470,   395,   392,   150,
     399,   468,    84,   400,   235,   469,   688,   689,   690,   691,
     692,   693,   401,   471,   813,   173,   109,   110,   200,    84,
     403,   157,   404,   472,    84,   405,   174,   190,   406,   215,
     201,   411,   414,   175,   416,   417,   420,   192,   421,   241,
     205,   216,   262,   158,   260,   473,   422,   277,   261,   176,
      84,   217,   177,   429,   430,   431,   474,   432,   433,   193,
     434,   255,   206,   298,   475,   436,   273,   476,   437,   282,
     195,   263,   438,   218,   439,   440,   444,   876,   196,   877,
     878,   197,   441,   256,   222,   299,   442,   443,   274,   448,
     449,   283,   223,   445,   446,   224,   447,   450,   451,    84,
     847,   848,   849,   850,   452,   453,   625,   300,   540,   541,
     542,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   235,   257,   236,   237,   258,   259,   454,   455,   555,
     456,   235,   457,   109,   110,   459,   460,   462,   463,   458,
     464,   482,   465,   109,   110,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   496,
     498,   499,   500,   501,   502,   503,   504,   505,   610,   507,
     508,   150,   510,   509,   511,   636,   636,   512,   513,   644,
     644,   515,   519,   516,   517,   520,   603,   522,   523,   298,
     524,   526,   529,   157,   530,   470,   525,   651,   651,   531,
     468,   527,   528,   618,   469,   532,    84,   533,   534,   535,
     537,   299,   471,   544,   538,   158,    84,   539,   543,   652,
     652,   545,   472,   547,   546,   548,   549,   550,   109,   110,
     551,   552,   571,   300,    28,   556,   557,   558,   792,   572,
     559,   560,   561,   562,   473,   573,   574,   575,   576,   577,
     578,   579,   584,   585,   586,   474,   587,   589,   590,   591,
     654,   658,   592,   475,   593,   662,   476,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   594,   595,   596,   597,   598,   599,   600,   601,   602,
     666,   684,   710,   712,   716,   620,   604,   605,   731,   720,
     732,   733,   734,   735,   743,   588,   742,   746,   745,   748,
     749,    84,   751,   752,   606,   758,   617,   759,   778,   760,
     761,   762,   763,   764,   765,   779,   773,   776,   782,   781,
     785,   787,   784,   788,   789,   790,   796,   791,   797,   793,
     836,   795,   794,   829,   830,   831,   832,   833,   834,   837,
     839,   840,   846,   845,   858,   852,   853,   890,   859,   867,
     854,   855,   856,   869,   863,   894,   636,   864,   896,   173,
     644,   895,   241,   262,   898,   260,   865,   900,   805,   261,
     174,   190,   810,   918,   868,   277,   899,   175,   651,   806,
     817,   192,   919,   920,   255,   923,   807,   273,   925,   924,
     818,   553,   263,   176,   926,   200,   177,   282,   215,   928,
     652,   461,   808,   193,   435,   809,   256,   201,   619,   274,
     216,   624,   819,   653,   195,   466,   825,   205,   798,   283,
     217,   827,   196,   820,   835,   197,   828,   824,   521,   800,
     495,   821,   799,   872,   822,   518,   802,   804,   801,   206,
     842,   497,   218,   514,   803,   841,   506,   711,   844,   843,
     536,   708,   838,   222,   888,   786,   897,   916,   927,     0,
       0,   223,     0,     0,   224,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   805,     0,
       0,     0,   810,     0,     0,     0,     0,     0,     0,   806,
     817,   879,     0,     0,     0,   880,   807,     0,     0,     0,
     818,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     879,     0,   808,   881,   880,   809,     0,     0,     0,     0,
       0,     0,   819,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   881,   820,     0,   882,     0,     0,     0,     0,
       0,   821,     0,     0,   822,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   882
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    68,    64,    65,    66,    67,    70,    69,    70,    71,
      72,   557,    70,    15,    65,    65,    66,    67,     5,    10,
       7,    65,     9,   750,    64,    65,    66,    67,     3,    69,
      70,    71,    72,     8,   750,    70,    60,    65,    12,    13,
      65,   750,    16,   750,     0,    19,    64,    65,    66,    67,
       7,    69,    70,    71,    72,    27,     3,     7,    65,     7,
      67,     8,     3,    14,    15,     3,    65,     8,    67,    65,
       8,    67,     3,    21,    22,    23,    24,     8,     3,     3,
      52,     6,    54,    55,     8,     7,    58,    59,    60,     7,
      64,    65,    64,    65,    42,    43,    44,     3,     7,    47,
      48,    49,     8,    51,   119,   120,   121,   122,     3,     3,
       7,     7,     6,     8,    62,   117,    64,    65,    66,    67,
      68,    69,    70,    71,    21,    22,    23,    24,    78,     3,
      78,    79,   123,   860,     8,   150,     3,     3,    86,     6,
       6,   132,   133,   134,   860,    42,    43,    44,     7,    46,
       7,   860,     3,   860,    51,    52,   147,     8,     7,     3,
     147,   148,   149,   150,     8,     7,     3,    64,    65,     7,
      67,     8,     7,   147,    71,   147,   147,    22,    23,    24,
      50,    78,     3,    11,     6,     3,    64,    65,     4,    86,
       8,     8,    20,    21,    22,    23,    24,    25,    26,   147,
      72,    73,    74,     3,   750,    50,    51,    52,     8,   755,
       3,    89,    90,     4,    42,    43,    44,    45,    46,    64,
      65,     4,    50,    51,     3,    22,    23,    24,    51,     8,
       3,     8,    77,    61,     3,     8,    64,    65,     3,     8,
      63,    64,    65,     8,     3,     3,     3,    75,    76,     8,
     147,     8,   100,   101,    51,     4,    80,    81,    82,    83,
      88,    85,     4,    91,    17,    18,   328,    64,    65,   147,
      98,    99,   126,     3,   102,   129,   130,   131,     8,    76,
       4,     4,     4,    80,    81,    82,    83,    84,    85,     4,
      87,     4,     4,     4,   318,   319,   363,     4,     8,   361,
       4,   363,   147,     8,    52,   363,    92,    93,    94,    95,
      96,    97,     3,   363,   860,   377,    64,    65,   380,   147,
       4,   361,     4,   363,   147,     8,   377,   377,     3,   391,
     380,     4,     4,   377,     4,     4,     4,   377,     4,   401,
     380,   391,   406,   361,   406,   363,     4,   409,   406,   377,
     147,   391,   377,   147,     4,     4,   363,     4,     4,   377,
       4,   401,   380,   425,   363,     4,   406,   363,   150,   409,
     377,   406,   150,   391,     4,     4,   148,   125,   377,   127,
     128,   377,     4,   401,   391,   425,     4,     4,   406,     4,
       4,   409,   391,   148,   148,   391,   148,     4,     4,   147,
      28,    29,    30,    31,     4,     4,    27,   425,   432,   433,
     434,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    52,    53,    54,    55,    56,    57,     4,     4,   453,
       4,    52,     4,    64,    65,     4,     4,     4,     4,   148,
       4,     4,   150,    64,    65,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     4,     4,     4,
       4,     4,     4,   148,   150,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   118,     4,
       4,   543,     4,   148,     4,   547,   548,     4,   150,   547,
     548,     4,     4,   150,   150,     4,   520,   150,     4,   561,
       4,     4,     4,   543,     4,   572,   148,   547,   548,   150,
     572,   148,   148,   537,   572,   150,   147,   150,     4,     4,
       4,   561,   572,   147,     7,   543,   147,     7,     7,   547,
     548,   147,   572,     7,   147,     7,     5,     5,    64,    65,
       5,     5,     8,   561,     7,     5,     5,     5,   150,     3,
       7,     7,     7,     5,   572,   147,   147,   147,     5,   147,
     147,   147,   147,     5,     7,   572,   147,   147,   147,   147,
       7,     7,   147,   572,   147,     7,   572,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   147,   147,   147,   147,   147,   147,   147,   147,   147,
       7,     7,     4,     7,     7,   124,   147,   147,     4,    87,
       4,     4,     4,     4,     3,   498,     6,     3,     6,     6,
       3,   147,     6,     3,   147,     6,   147,     3,     6,     4,
       4,     4,     4,     4,     4,     3,   147,   147,     3,     6,
       4,     4,     8,     4,     4,     4,     4,   148,     4,   148,
       4,   148,   150,   148,   148,   148,   148,   148,   148,     4,
       6,     3,     5,     4,     8,   147,   147,     4,     8,     8,
     147,   147,   147,     7,   147,     4,   738,   147,     4,   741,
     738,   148,   744,   747,     5,   747,   147,     7,   750,   747,
     741,   741,   750,     4,   147,   757,   147,   741,   738,   750,
     750,   741,     4,     4,   744,     4,   750,   747,   148,   150,
     750,   452,   747,   741,   148,   777,   741,   757,   780,   147,
     738,   355,   750,   741,   328,   750,   744,   777,   538,   747,
     780,   543,   750,   548,   741,   361,   753,   777,   738,   757,
     780,   757,   741,   750,   766,   741,   759,   752,   409,   743,
     377,   750,   741,   860,   750,   406,   746,   749,   744,   777,
     779,   380,   780,   401,   747,   777,   391,   572,   782,   780,
     425,   561,   770,   780,   874,   724,   892,   904,   921,    -1,
      -1,   780,    -1,    -1,   780,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   860,    -1,
      -1,    -1,   860,    -1,    -1,    -1,    -1,    -1,    -1,   860,
     860,   873,    -1,    -1,    -1,   873,   860,    -1,    -1,    -1,
     860,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     892,    -1,   860,   873,   892,   860,    -1,    -1,    -1,    -1,
      -1,    -1,   860,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   892,   860,    -1,   873,    -1,    -1,    -1,    -1,
      -1,   860,    -1,    -1,   860,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   892
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     0,     5,     7,     9,
     147,   148,   149,   150,   165,   166,   167,   172,     7,   181,
       7,   187,     7,   201,     7,   277,     7,   358,     7,   374,
       7,   310,     7,   316,     7,   340,     7,   253,     7,   426,
     173,   168,   182,   188,   202,   278,   359,   375,   311,   317,
     341,   254,   427,   165,   174,   175,   147,   170,   171,    10,
     123,   132,   133,   134,   147,   180,   183,   184,   185,   453,
     455,   457,   459,    11,    20,    21,    22,    23,    24,    25,
      26,    42,    43,    44,    45,    46,    50,    51,    61,    64,
      65,    75,    76,    88,    91,    98,    99,   102,   180,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   212,   214,
     238,   247,   261,   271,   300,   308,   334,   364,   366,   379,
     381,   383,   405,   415,   416,   424,    12,    13,    16,    19,
     180,   199,   200,   203,   205,   208,   211,   364,   366,     7,
      47,    48,    49,    62,    66,    67,    68,    69,    70,    71,
      78,    79,    86,   180,   191,   192,   193,   196,   279,   280,
     281,   283,   285,   287,   289,   291,   293,   295,   298,   299,
     334,   352,   364,   366,   368,   379,   381,   383,   401,    63,
     180,   334,   360,   361,   362,   364,   366,    76,    80,    81,
      82,    83,    84,    85,    87,   180,   334,   364,   366,   376,
     377,   378,   379,   381,   383,   385,   387,   389,   391,   393,
     395,   397,   399,   308,    27,    52,    54,    55,    58,    59,
      60,   180,   228,   318,   319,   320,   321,   322,   323,   324,
     326,   328,   330,   331,   333,   364,   366,    53,    56,    57,
     180,   228,   322,   328,   342,   343,   344,   345,   346,   348,
     349,   350,   351,   364,   366,    89,    90,   180,   255,   256,
     257,   259,   364,   366,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   180,   364,
     366,   428,   429,   430,   431,   433,   435,   436,   438,   439,
     440,   443,   445,   446,   447,   448,   451,     6,     3,     4,
       8,     3,   186,   460,   454,   456,   458,     4,     3,     8,
     198,     4,     4,   380,   382,   384,   213,   215,     4,     4,
       4,     4,   272,   309,   335,   301,   365,   367,   239,   406,
     248,   262,     4,   417,   425,     3,     8,   204,   206,   209,
       4,     3,     8,   408,   284,   286,   288,   353,   282,   290,
     292,     4,     4,   296,   294,   369,   402,     3,     8,   363,
       3,     8,   400,   388,   390,   394,   392,   398,   396,   386,
       8,     3,     8,   325,   229,     4,   329,   327,   332,     4,
       8,     3,   347,     4,     4,     8,     3,   258,   260,     3,
       8,     4,   432,   434,     4,   437,     4,     4,   441,   444,
       4,     4,     4,   449,   452,     3,     8,   165,   165,   147,
       4,     4,     4,     4,     4,   184,     4,   150,   150,     4,
       4,     4,     4,     4,   148,   148,   148,   148,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   148,     4,
       4,   190,     4,     4,     4,   150,   200,    77,   180,   228,
     308,   334,   364,   366,   379,   381,   383,   409,   410,   411,
     412,   413,     4,     4,     4,     4,     4,     4,     4,   148,
     150,     4,     4,     4,     4,   280,     4,   361,     4,     4,
       4,     4,     4,     4,     4,     4,   378,     4,     4,   148,
       4,     4,     4,   150,   320,     4,   150,   150,   344,     4,
       4,   256,   150,     4,     4,   148,     4,   148,   148,     4,
       4,   150,   150,   150,     4,     4,   429,     4,     7,     7,
     165,   165,   165,     7,   147,   147,   147,     7,     7,     5,
       5,     5,     5,   167,   169,   165,     5,     5,     5,     7,
       7,     7,     5,   176,    14,    15,   207,    17,    18,   210,
     414,     8,     3,   147,   147,   147,     5,   147,   147,   147,
      72,    73,    74,   297,   147,     5,     7,   147,   176,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   165,   147,   147,   147,    15,   117,   442,
     118,   119,   120,   121,   122,   150,   450,   147,   165,   189,
     124,   461,   462,   463,   199,    27,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,   180,   216,   217,   218,
     221,   223,   225,   227,   228,   230,   231,   232,   233,   234,
     236,   364,   366,   216,     7,   273,   274,   275,     7,   312,
     313,   314,     7,   336,   337,   338,     7,   302,   303,   304,
      80,    81,    82,    83,    85,   240,   241,   242,   243,   244,
     245,   246,   293,   407,     7,   249,   250,   251,    92,    93,
      94,    95,    96,    97,   263,   264,   265,   266,   267,   268,
     269,   270,   100,   101,   418,   419,   420,   422,   428,   177,
       4,   411,     7,   354,   355,   356,     7,   370,   371,   372,
      87,   403,     8,   464,     3,     8,     8,   219,   222,   224,
     226,     4,     4,     4,     4,     4,   235,   237,     3,     8,
       8,   276,     6,     3,   315,     6,     3,   339,     6,     3,
     305,     6,     3,     3,     6,     3,     6,   252,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   421,   423,
       3,     8,     8,   147,   178,   179,   147,   357,     6,     3,
     373,     6,     3,   404,     8,     4,   462,     4,     4,     4,
       4,   148,   150,   148,   150,   148,     4,     4,   217,   279,
     275,   318,   314,   342,   338,   180,   191,   192,   193,   196,
     228,   271,   289,   293,   295,   306,   307,   334,   364,   366,
     379,   381,   383,   401,   304,   241,   293,   255,   251,   148,
     148,   148,   148,   148,   148,   264,     4,     4,   419,     6,
       3,   360,   356,   376,   372,     4,     5,    28,    29,    30,
      31,   220,   147,   147,   147,   147,   147,     8,     8,     8,
       3,     8,     8,   147,   147,   147,     8,     8,   147,     7,
     465,   466,   307,   467,     3,     6,   125,   127,   128,   180,
     228,   364,   366,   468,   469,   470,   471,   473,   466,   474,
       4,   472,     3,     8,     4,   148,     4,   469,     5,   147,
       7,   475,   476,   477,     3,     6,   126,   129,   130,   131,
     478,   479,   480,   482,   483,   484,   476,   481,     4,     4,
       4,     3,     8,     4,   150,   148,   148,   479,   147
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   151,   153,   152,   154,   152,   155,   152,   156,   152,
     157,   152,   158,   152,   159,   152,   160,   152,   161,   152,
     162,   152,   163,   152,   164,   152,   165,   165,   165,   165,
     165,   165,   165,   166,   168,   167,   169,   170,   170,   171,
     171,   173,   172,   174,   174,   175,   175,   177,   176,   178,
     178,   179,   179,   180,   182,   181,   183,   183,   184,   184,
     184,   184,   184,   184,   186,   185,   188,   187,   189,   189,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   191,   192,   193,   194,
     195,   196,   198,   197,   199,   199,   200,   200,   200,   200,
     200,   200,   200,   202,   201,   204,   203,   206,   205,   207,
     207,   209,   208,   210,   210,   211,   213,   212,   215,   214,
     216,   216,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   219,   218,   220,
     220,   220,   220,   222,   221,   224,   223,   226,   225,   227,
     229,   228,   230,   231,   232,   233,   235,   234,   237,   236,
     239,   238,   240,   240,   241,   241,   241,   241,   241,   242,
     243,   244,   245,   246,   248,   247,   249,   249,   250,   250,
     252,   251,   254,   253,   255,   255,   256,   256,   256,   256,
     256,   258,   257,   260,   259,   262,   261,   263,   263,   264,
     264,   264,   264,   264,   264,   265,   266,   267,   268,   269,
     270,   272,   271,   273,   273,   274,   274,   276,   275,   278,
     277,   279,   279,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   282,   281,   284,
     283,   286,   285,   288,   287,   290,   289,   292,   291,   294,
     293,   296,   295,   297,   297,   297,   298,   299,   301,   300,
     302,   302,   303,   303,   305,   304,   306,   306,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   309,   308,   311,   310,   312,
     312,   313,   313,   315,   314,   317,   316,   318,   318,   319,
     319,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   321,   322,   323,   325,   324,   327,   326,   329,   328,
     330,   332,   331,   333,   335,   334,   336,   336,   337,   337,
     339,   338,   341,   340,   342,   342,   343,   343,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   345,   347,   346,
     348,   349,   350,   351,   353,   352,   354,   354,   355,   355,
     357,   356,   359,   358,   360,   360,   361,   361,   361,   361,
     361,   363,   362,   365,   364,   367,   366,   369,   368,   370,
     370,   371,   371,   373,   372,   375,   374,   376,   376,   377,
     377,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   380,   379,   382,   381,
     384,   383,   386,   385,   388,   387,   390,   389,   392,   391,
     394,   393,   396,   395,   398,   397,   400,   399,   402,   401,
     404,   403,   406,   405,   407,   407,   408,   293,   409,   409,
     410,   410,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   412,   414,   413,   415,   417,   416,   418,   418,
     419,   419,   421,   420,   423,   422,   425,   424,   427,   426,
     428,   428,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   430,
     432,   431,   434,   433,   435,   437,   436,   438,   439,   441,
     440,   442,   442,   444,   443,   445,   446,   447,   449,   448,
     450,   450,   450,   450,   450,   452,   451,   454,   453,   456,
     455,   458,   457,   460,   459,   461,   461,   462,   464,   463,
     465,   465,   467,   466,   468,   468,   469,   469,   469,   469,
     469,   469,   469,   470,   472,   471,   474,   473,   475,   475,
     477,   476,   478,   478,   479,   479,   479,   479,   481,   480,
     482,   483,   484
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
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
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     6,
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
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
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
  "socket_type", "outbound_interface", "$@23", "outbound_interface_value",
  "re_detect", "lease_database", "$@24", "hosts_database", "$@25",
  "database_map_params", "database_map_param", "database_type", "$@26",
  "db_type", "user", "$@27", "password", "$@28", "host", "$@29", "port",
  "name", "$@30", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@31", "keyspace", "$@32",
  "host_reservation_identifiers", "$@33",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@34", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@35",
  "sub_hooks_library", "$@36", "hooks_params", "hooks_param", "library",
  "$@37", "parameters", "$@38", "expired_leases_processing", "$@39",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@40",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@41",
  "sub_subnet4", "$@42", "subnet4_params", "subnet4_param", "subnet",
  "$@43", "subnet_4o6_interface", "$@44", "subnet_4o6_interface_id",
  "$@45", "subnet_4o6_subnet", "$@46", "interface", "$@47", "interface_id",
  "$@48", "client_class", "$@49", "reservation_mode", "$@50", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@51",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@52", "shared_network_params", "shared_network_param",
  "option_def_list", "$@53", "sub_option_def_list", "$@54",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@55", "sub_option_def", "$@56",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@57",
  "option_def_record_types", "$@58", "space", "$@59", "option_def_space",
  "option_def_encapsulate", "$@60", "option_def_array", "option_data_list",
  "$@61", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@62", "sub_option_data", "$@63",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@64",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@65", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@66", "sub_pool4", "$@67",
  "pool_params", "pool_param", "pool_entry", "$@68", "user_context",
  "$@69", "comment", "$@70", "reservations", "$@71", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@72", "sub_reservation",
  "$@73", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@74", "server_hostname", "$@75",
  "boot_file_name", "$@76", "ip_address", "$@77", "duid", "$@78",
  "hw_address", "$@79", "client_id_value", "$@80", "circuit_id_value",
  "$@81", "flex_id_value", "$@82", "hostname", "$@83",
  "reservation_client_classes", "$@84", "relay", "$@85", "relay_map",
  "$@86", "client_classes", "$@87", "client_classes_list", "$@88",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@89",
  "dhcp4o6_port", "control_socket", "$@90", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@91",
  "control_socket_name", "$@92", "dhcp_ddns", "$@93", "sub_dhcp_ddns",
  "$@94", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@95", "server_ip", "$@96", "server_port",
  "sender_ip", "$@97", "sender_port", "max_queue_size", "ncr_protocol",
  "$@98", "ncr_protocol_value", "ncr_format", "$@99",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@100", "replace_client_name_value",
  "generated_prefix", "$@101", "dhcp6_json_object", "$@102",
  "dhcpddns_json_object", "$@103", "control_agent_json_object", "$@104",
  "logging_object", "$@105", "logging_params", "logging_param", "loggers",
  "$@106", "loggers_entries", "logger_entry", "$@107", "logger_params",
  "logger_param", "debuglevel", "severity", "$@108", "output_options_list",
  "$@109", "output_options_list_content", "output_entry", "$@110",
  "output_params_list", "output_params", "output", "$@111", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   234,   234,   234,   235,   235,   236,   236,   237,   237,
     238,   238,   239,   239,   240,   240,   241,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   253,   254,   255,   256,
     257,   258,   259,   262,   267,   267,   278,   281,   282,   285,
     289,   296,   296,   303,   304,   307,   311,   318,   318,   325,
     326,   329,   333,   344,   354,   354,   370,   371,   375,   376,
     377,   378,   379,   380,   383,   383,   398,   398,   407,   408,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   441,   446,   451,   456,
     461,   466,   472,   472,   483,   484,   487,   488,   489,   490,
     491,   492,   493,   496,   496,   505,   505,   515,   515,   522,
     523,   526,   526,   533,   535,   539,   545,   545,   557,   557,
     569,   570,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   590,   590,   597,
     598,   599,   600,   603,   603,   611,   611,   619,   619,   627,
     632,   632,   640,   645,   650,   655,   660,   660,   668,   668,
     677,   677,   687,   688,   691,   692,   693,   694,   695,   698,
     703,   708,   713,   718,   723,   723,   733,   734,   737,   738,
     741,   741,   751,   751,   761,   762,   765,   766,   767,   768,
     769,   772,   772,   780,   780,   788,   788,   799,   800,   803,
     804,   805,   806,   807,   808,   811,   816,   821,   826,   831,
     836,   844,   844,   857,   858,   861,   862,   869,   869,   895,
     895,   906,   907,   911,   912,   913,   914,   915,   916,   917,
     918,   919,   920,   921,   922,   923,   924,   925,   926,   927,
     928,   929,   930,   931,   932,   933,   934,   937,   937,   945,
     945,   953,   953,   961,   961,   969,   969,   977,   977,   985,
     985,   993,   993,  1000,  1001,  1002,  1005,  1010,  1017,  1017,
    1028,  1029,  1033,  1034,  1037,  1037,  1045,  1046,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,
    1061,  1062,  1063,  1064,  1065,  1072,  1072,  1085,  1085,  1094,
    1095,  1098,  1099,  1104,  1104,  1119,  1119,  1133,  1134,  1137,
    1138,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,  1149,
    1150,  1153,  1155,  1160,  1162,  1162,  1170,  1170,  1178,  1178,
    1186,  1188,  1188,  1196,  1205,  1205,  1217,  1218,  1223,  1224,
    1229,  1229,  1241,  1241,  1253,  1254,  1259,  1260,  1265,  1266,
    1267,  1268,  1269,  1270,  1271,  1272,  1273,  1276,  1278,  1278,
    1286,  1288,  1290,  1295,  1303,  1303,  1315,  1316,  1319,  1320,
    1323,  1323,  1333,  1333,  1343,  1344,  1347,  1348,  1349,  1350,
    1351,  1354,  1354,  1362,  1362,  1369,  1369,  1381,  1381,  1391,
    1392,  1395,  1396,  1399,  1399,  1408,  1408,  1417,  1418,  1421,
    1422,  1426,  1427,  1428,  1429,  1430,  1431,  1432,  1433,  1434,
    1435,  1436,  1437,  1438,  1439,  1440,  1443,  1443,  1451,  1451,
    1459,  1459,  1467,  1467,  1475,  1475,  1483,  1483,  1491,  1491,
    1499,  1499,  1507,  1507,  1515,  1515,  1523,  1523,  1536,  1536,
    1546,  1546,  1557,  1557,  1567,  1568,  1571,  1571,  1581,  1582,
    1585,  1586,  1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,
    1597,  1598,  1601,  1603,  1603,  1615,  1622,  1622,  1632,  1633,
    1636,  1637,  1640,  1640,  1648,  1648,  1658,  1658,  1670,  1670,
    1680,  1681,  1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,
    1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,  1703,
    1708,  1708,  1716,  1716,  1724,  1729,  1729,  1737,  1742,  1747,
    1747,  1755,  1756,  1759,  1759,  1767,  1772,  1777,  1782,  1782,
    1790,  1793,  1796,  1799,  1802,  1808,  1808,  1818,  1818,  1825,
    1825,  1832,  1832,  1844,  1844,  1857,  1858,  1862,  1866,  1866,
    1878,  1879,  1883,  1883,  1891,  1892,  1895,  1896,  1897,  1898,
    1899,  1900,  1901,  1904,  1909,  1909,  1917,  1917,  1927,  1928,
    1931,  1931,  1939,  1940,  1943,  1944,  1945,  1946,  1949,  1949,
    1957,  1962,  1967
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
#line 4428 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1972 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
