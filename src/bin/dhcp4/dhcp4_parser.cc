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

  case 110:
#line 493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 222:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 962 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 970 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 986 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1877 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 994 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1030 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1034 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1097 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1101 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1148 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1165 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1173 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1183 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1222 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1234 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 346:
#line 1238 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1314 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1328 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2311 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
    e->set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.stack_.back()->combine_set("user-context", e);
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1442 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2468 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2486 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2504 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1490 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2674 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1609 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2845 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2937 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2980 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1781 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2996 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3013 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1817 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3082 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3140 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1900 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3205 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3232 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3241 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -717;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     259,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,    59,    18,    19,    56,    58,    76,    80,
      82,    91,    95,   126,   137,   145,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
      18,    17,     4,   134,    94,    26,    83,   164,   143,   142,
     220,   -28,   275,  -717,   166,   202,   219,   216,   232,  -717,
    -717,  -717,  -717,  -717,   237,  -717,    52,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,   238,   239,  -717,  -717,  -717,  -717,
    -717,   248,   250,   256,   274,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,   293,  -717,  -717,  -717,    64,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,   304,
      68,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,   305,   321,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,   115,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,   122,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,   330,   337,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,   335,  -717,
    -717,   340,  -717,  -717,  -717,   342,  -717,  -717,   341,   345,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,   350,   353,  -717,  -717,  -717,  -717,   351,
     355,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,   123,  -717,  -717,  -717,   356,  -717,  -717,   357,  -717,
     358,   359,  -717,  -717,   360,   361,   362,  -717,  -717,  -717,
     167,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,    18,    18,  -717,
     221,   365,   366,   367,   371,   372,  -717,     4,  -717,   388,
     257,   258,   402,   405,   406,   407,   408,   265,   266,   267,
     268,   413,   414,   415,   416,   417,   419,   420,   421,   422,
     423,   280,   425,   426,   134,  -717,   427,   428,   429,   286,
      94,  -717,    34,   430,   431,   433,   434,   435,   436,   437,
     294,   296,   439,   440,   441,   443,    26,  -717,   444,    83,
    -717,   445,   446,   447,   448,   449,   450,   451,   452,  -717,
     164,  -717,   453,   455,   313,   456,   458,   459,   314,  -717,
     142,   463,   318,   319,  -717,   220,   466,   467,    73,  -717,
     324,   472,   473,   332,   474,   333,   334,   475,   479,   338,
     339,   344,   480,   481,   275,  -717,  -717,  -717,   483,   484,
     485,    18,    18,    18,  -717,   488,  -717,  -717,   349,   352,
     354,   491,   493,  -717,  -717,  -717,  -717,   497,   498,   499,
     500,   501,    18,   502,   505,   506,   507,  -717,   508,   509,
    -717,   512,    30,   165,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,   504,   503,  -717,  -717,  -717,   373,
     374,   375,   513,   376,   377,   378,  -717,  -717,    43,   379,
     514,   520,  -717,   381,  -717,   512,   384,   385,   386,   389,
     390,   391,   392,  -717,   393,   394,  -717,   395,   396,   397,
    -717,  -717,   398,  -717,  -717,  -717,   399,    18,  -717,  -717,
     400,   401,  -717,   403,  -717,  -717,     3,   438,  -717,  -717,
    -717,   -68,   404,  -717,    18,   134,   411,  -717,  -717,  -717,
      94,  -717,  -717,  -717,   230,   230,   542,   545,   546,   547,
    -717,  -717,  -717,   146,    36,   548,   124,   112,   275,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,   553,  -717,    34,
    -717,  -717,  -717,   551,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,   552,   476,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,   253,  -717,   276,  -717,
    -717,   277,  -717,  -717,  -717,  -717,   556,   557,   558,   560,
     561,  -717,  -717,  -717,   284,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,   285,  -717,
     562,   510,  -717,  -717,   563,   564,  -717,  -717,   565,   567,
    -717,  -717,   566,   570,  -717,  -717,  -717,  -717,  -717,  -717,
     147,  -717,  -717,  -717,  -717,  -717,  -717,  -717,   168,  -717,
     568,   572,  -717,   573,   574,   575,   576,   577,   578,   288,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,   291,
    -717,  -717,  -717,   292,   442,   454,  -717,  -717,   579,   580,
    -717,  -717,   581,   583,  -717,  -717,   582,  -717,   584,   411,
    -717,  -717,   587,   588,   589,   590,   418,   457,   460,   461,
     462,   591,   592,   230,  -717,  -717,    26,  -717,   542,   142,
    -717,   545,   220,  -717,   546,    57,  -717,   547,   146,  -717,
      36,  -717,   -28,  -717,   548,   464,   465,   468,   469,   470,
     471,   124,  -717,   593,   594,   112,  -717,  -717,  -717,   596,
     597,  -717,    83,  -717,   551,   164,  -717,   552,   595,  -717,
     571,  -717,   161,   477,   478,   482,  -717,  -717,  -717,  -717,
    -717,   486,   487,  -717,   295,  -717,   598,  -717,   601,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
     298,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,   302,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,   489,   490,  -717,  -717,   492,   309,  -717,   606,  -717,
     494,   608,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,    57,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,   208,  -717,  -717,    14,   608,
    -717,  -717,   599,  -717,  -717,  -717,   312,  -717,  -717,  -717,
    -717,  -717,   600,   495,   616,    14,  -717,   617,  -717,   511,
    -717,   614,  -717,  -717,   247,  -717,   108,   614,  -717,  -717,
     619,   622,   623,   331,  -717,  -717,  -717,  -717,  -717,  -717,
     624,   496,   517,   521,   108,  -717,   515,  -717,  -717,  -717,
    -717,  -717
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   110,     9,   222,    11,   373,    13,   396,    15,
     300,    17,   308,    19,   345,    21,   187,    23,   475,    25,
      43,    37,     0,     0,     0,     0,     0,   398,     0,   310,
     347,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     528,   522,   524,   526,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   102,     0,     0,   415,   417,   419,   123,
     125,     0,     0,     0,     0,   214,   298,   337,   271,   384,
     386,   165,   441,   179,   198,     0,   463,   473,    95,     0,
      68,    70,    71,    72,    73,    88,    89,    76,    77,    78,
      79,    83,    84,    74,    75,    81,    82,    93,    94,    90,
      91,    92,    80,    85,    86,    87,   112,   114,   118,     0,
       0,   104,   106,   107,   108,   109,   445,   252,   254,   256,
     365,   250,   258,   260,     0,     0,   264,   262,   388,   437,
     249,   226,   227,   228,   240,     0,   224,   231,   244,   245,
     246,   232,   233,   236,   238,   234,   235,   229,   230,   247,
     248,   237,   241,   242,   243,   239,   382,   381,   378,     0,
     375,   377,   379,   380,   435,   423,   425,   429,   427,   433,
     431,   421,   414,   410,     0,   399,   400,   411,   412,   413,
     407,   402,   408,   404,   405,   406,   409,   403,     0,   327,
     155,     0,   331,   329,   334,     0,   323,   324,     0,   311,
     312,   314,   326,   315,   316,   317,   333,   318,   319,   320,
     321,   322,   359,     0,     0,   357,   358,   361,   362,     0,
     348,   349,   351,   352,   353,   354,   355,   356,   194,   196,
     191,     0,   189,   192,   193,     0,   495,   497,     0,   500,
       0,     0,   504,   508,     0,     0,     0,   513,   520,   493,
       0,   477,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,    42,     0,     0,    35,
       0,     0,     0,     0,     0,     0,    53,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,     0,     0,
       0,   111,   447,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   223,     0,     0,
     374,     0,     0,     0,     0,     0,     0,     0,     0,   397,
       0,   301,     0,     0,     0,     0,     0,     0,     0,   309,
       0,     0,     0,     0,   346,     0,     0,     0,     0,   188,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   476,    46,    39,     0,     0,
       0,     0,     0,     0,    57,     0,   100,   101,     0,     0,
       0,     0,     0,    96,    97,    98,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   462,     0,     0,
      69,     0,     0,     0,   122,   105,   460,   458,   459,   453,
     454,   455,   456,   457,     0,   448,   449,   451,   452,     0,
       0,     0,     0,     0,     0,     0,   269,   270,     0,     0,
       0,     0,   225,     0,   376,     0,     0,     0,     0,     0,
       0,     0,     0,   401,     0,     0,   325,     0,     0,     0,
     336,   313,     0,   363,   364,   350,     0,     0,   190,   494,
       0,     0,   499,     0,   502,   503,     0,     0,   510,   511,
     512,     0,     0,   478,     0,     0,     0,   523,   525,   527,
       0,   416,   418,   420,     0,     0,   216,   302,   339,   273,
      36,   385,   387,     0,     0,   181,     0,     0,     0,    47,
     113,   116,   117,   115,   120,   121,   119,     0,   446,     0,
     253,   255,   257,   367,   251,   259,   261,   266,   267,   268,
     265,   263,   390,     0,   383,   436,   424,   426,   430,   428,
     434,   432,   422,   328,   156,   332,   330,   335,   360,   195,
     197,   496,   498,   501,   506,   507,   505,   509,   515,   516,
     517,   518,   519,   514,   521,    40,     0,   533,     0,   530,
     532,     0,   142,   148,   150,   152,     0,     0,     0,     0,
       0,   161,   163,   141,     0,   127,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     0,   220,
       0,   217,   218,   306,     0,   303,   304,   343,     0,   340,
     341,   277,     0,   274,   275,   174,   175,   176,   177,   178,
       0,   167,   169,   170,   171,   172,   173,   443,     0,   185,
       0,   182,   183,     0,     0,     0,     0,     0,     0,     0,
     200,   202,   203,   204,   205,   206,   207,   469,   471,     0,
     465,   467,   468,     0,    49,     0,   450,   371,     0,   368,
     369,   394,     0,   391,   392,   439,     0,    65,     0,     0,
     529,   103,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   124,   126,     0,   215,     0,   310,
     299,     0,   347,   338,     0,     0,   272,     0,     0,   166,
       0,   442,     0,   180,     0,     0,     0,     0,     0,     0,
       0,     0,   199,     0,     0,     0,   464,   474,    51,     0,
      50,   461,     0,   366,     0,   398,   389,     0,     0,   438,
       0,   531,     0,     0,     0,     0,   154,   157,   158,   159,
     160,     0,     0,   128,     0,   219,     0,   305,     0,   342,
     297,   294,   284,   285,   287,   281,   282,   283,   293,   292,
       0,   279,   286,   295,   296,   288,   289,   290,   291,   276,
     168,   444,     0,   184,   208,   209,   210,   211,   212,   213,
     201,     0,     0,   466,    48,     0,     0,   370,     0,   393,
       0,     0,   144,   145,   146,   147,   143,   149,   151,   153,
     162,   164,   221,   307,   344,     0,   278,   186,   470,   472,
      52,   372,   395,   440,   537,     0,   535,   280,     0,     0,
     534,   549,     0,   547,   545,   541,     0,   539,   543,   544,
     542,   536,     0,     0,     0,     0,   538,     0,   546,     0,
     540,     0,   548,   553,     0,   551,     0,     0,   550,   561,
       0,     0,     0,     0,   555,   557,   558,   559,   560,   552,
       0,     0,     0,     0,     0,   554,     0,   563,   564,   565,
     556,   562
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,   -49,  -717,   189,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,    99,  -717,  -717,  -717,   -62,
    -717,  -717,  -717,   315,  -717,  -717,  -717,  -717,   106,   261,
     -52,   -31,   -24,  -717,  -717,   -19,  -717,  -717,   105,   290,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,   103,   -81,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,   -69,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
     -94,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
     -99,  -717,  -717,  -717,   -95,   251,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -103,  -717,  -717,  -717,  -717,  -717,  -717,
    -716,  -717,  -717,  -717,   -78,  -717,  -717,  -717,   -75,   287,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -713,  -717,
    -717,  -717,  -532,  -717,  -705,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,   -85,  -717,  -717,  -190,   -66,  -717,  -717,
    -717,  -717,  -717,   -74,  -717,  -717,  -717,   -73,  -717,   269,
    -717,   -64,  -717,  -717,  -717,  -717,  -717,   -39,  -717,  -717,
    -717,  -717,  -717,   -50,  -717,  -717,  -717,   -63,  -717,  -717,
    -717,   -72,  -717,   282,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,   -92,  -717,  -717,  -717,   -87,
     310,  -717,  -717,   -45,  -717,   -37,  -717,  -717,  -717,  -717,
    -717,   -89,  -717,  -717,  -717,   -83,  -717,   306,   -30,  -717,
     -29,  -717,   -25,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -696,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
     128,  -717,  -717,  -717,  -717,  -717,  -717,  -717,   -67,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,   151,   299,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,  -717,
    -717,   -18,  -717,  -717,  -717,  -165,  -717,  -717,  -167,  -717,
    -717,  -717,  -717,  -717,  -717,  -178,  -717,  -717,  -186,  -717,
    -717,  -717,  -717,  -717
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   541,    77,
      78,    37,    60,    74,    75,   550,   694,   759,   760,   118,
      39,    62,    86,    87,    88,   311,    41,    63,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   319,   150,   151,
      43,    64,   152,   346,   153,   347,   553,   154,   348,   556,
     155,   128,   325,   129,   326,   624,   625,   626,   712,   836,
     627,   713,   628,   714,   629,   715,   630,   237,   383,   632,
     633,   634,   635,   636,   721,   637,   722,   130,   337,   660,
     661,   662,   663,   664,   665,   666,   131,   339,   670,   671,
     672,   742,    57,    71,   271,   272,   273,   396,   274,   397,
     132,   340,   679,   680,   681,   682,   683,   684,   685,   686,
     133,   331,   640,   641,   642,   726,    45,    65,   175,   176,
     177,   357,   178,   353,   179,   354,   180,   355,   181,   358,
     182,   359,   183,   363,   184,   362,   570,   185,   186,   134,
     334,   652,   653,   654,   735,   800,   801,   135,   332,    51,
      68,   644,   645,   646,   729,    53,    69,   238,   239,   240,
     241,   242,   243,   244,   382,   245,   386,   246,   385,   247,
     248,   387,   249,   136,   333,   648,   649,   650,   732,    55,
      70,   259,   260,   261,   262,   263,   391,   264,   265,   266,
     267,   188,   356,   698,   699,   700,   762,    47,    66,   199,
     200,   201,   368,   137,   335,   138,   336,   191,   364,   702,
     703,   704,   765,    49,    67,   214,   215,   216,   139,   322,
     140,   323,   141,   324,   220,   378,   221,   372,   222,   373,
     223,   375,   224,   374,   225,   377,   226,   376,   227,   371,
     195,   365,   706,   768,   142,   338,   668,   352,   464,   465,
     466,   467,   468,   557,   143,   144,   342,   689,   690,   691,
     753,   692,   754,   145,   343,    59,    72,   290,   291,   292,
     293,   401,   294,   402,   295,   296,   404,   297,   298,   299,
     407,   596,   300,   408,   301,   302,   303,   304,   412,   603,
     305,   413,    89,   313,    90,   314,    91,   315,    92,   312,
     608,   609,   610,   708,   855,   856,   858,   866,   867,   868,
     869,   874,   870,   872,   884,   885,   886,   893,   894,   895,
     900,   896,   897,   898
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   256,   228,   170,   197,   212,   257,   236,   255,   270,
     289,    73,   667,   171,    79,   187,   198,   213,   594,   796,
     189,   202,   797,    27,   250,    28,    38,    29,   190,   203,
     799,   258,   251,   156,   172,   192,   193,   217,   218,   808,
     194,   173,   219,   156,   551,   552,   174,    95,    96,    97,
      98,   598,   599,   600,   601,   317,    96,    97,    98,    26,
     318,   268,   269,    40,   156,    42,   230,   344,   101,   102,
     103,   350,   345,   157,   158,   159,   351,   107,    95,    96,
      97,    98,   602,    44,   106,   107,   230,    46,   160,    48,
     109,   110,   161,   162,   163,   164,   165,   166,    50,   101,
     102,   103,    52,   105,   167,   168,   146,   147,   107,   230,
     148,   456,   169,   149,   167,   567,   568,   569,   366,    84,
     595,   109,   110,   367,   162,   369,   398,    80,   166,   796,
     370,   399,   797,    54,   107,   167,    81,    82,    83,   861,
     799,   862,   863,   169,    56,    93,   196,   109,   110,   808,
     738,    84,    58,   739,    94,    95,    96,    97,    98,    99,
     100,    84,   268,   269,    76,    30,    31,    32,    33,   229,
     414,   740,   306,    84,   741,   415,   101,   102,   103,   104,
     105,    84,   554,   555,   106,   107,    96,    97,    98,   832,
     833,   834,   835,   106,   230,   108,   231,   232,   109,   110,
     233,   234,   235,   798,    84,   307,   109,   110,   811,   111,
     112,   859,   687,   688,   860,   107,   673,   674,   675,   676,
     677,   678,   113,   308,   309,   114,   655,   656,   657,   658,
      84,   659,   115,   116,   889,   310,   117,   890,   891,   892,
     204,   316,   320,   321,   205,   206,   207,   208,   209,   210,
     887,   211,   327,   888,   328,    85,   344,   612,   416,   417,
     329,   707,   613,   614,   615,   616,   617,   618,   619,   620,
     621,   622,   230,   252,   231,   232,   253,   254,   330,   709,
     350,    84,   230,   458,   710,   711,   459,   723,   723,    84,
     457,   751,   724,   725,   755,   414,   752,   341,   366,   756,
     757,   845,   460,   842,   170,   398,   846,   197,   349,   360,
     847,    84,   369,   798,   171,   875,   187,   851,   212,   198,
     876,   189,   461,   462,   202,   361,   256,   463,   236,   190,
     213,   257,   203,   255,   904,   172,   192,   193,   379,   905,
     380,   194,   173,   381,   384,   250,   388,   174,   390,   389,
     217,   218,   289,   251,   392,   219,   258,   393,   395,   394,
     400,   403,   405,   406,   409,   410,   411,    84,   418,   419,
     420,   421,   527,   528,   529,   422,   423,    84,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   425,   542,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,   428,   426,   427,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,    84,   442,   443,   444,   445,   446,   447,   448,
     449,   451,   452,   453,   469,   470,   454,   471,   472,   473,
     474,   475,   476,   478,   479,   480,   477,   481,   483,   485,
     486,   487,   488,   489,   490,   491,   492,   494,   590,   495,
     497,   496,   498,   499,   500,   631,   631,   502,   503,   504,
     506,   507,   623,   623,   509,   605,   510,   511,   513,   516,
     512,   514,   515,   517,   521,   522,   289,   524,   518,   519,
     458,   525,   526,   459,   520,   530,   531,   457,   534,   532,
     535,   533,   536,   537,   538,   539,   559,   543,    28,   460,
     544,   545,   558,   728,   546,   547,   548,   549,   563,   572,
     560,   561,   562,   564,   565,   566,   571,   573,   574,   461,
     462,   576,   577,   578,   463,   607,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   591,   592,   639,
     593,   604,   643,   647,   651,   669,   597,   695,   697,   701,
     716,   717,   718,   705,   719,   720,   776,   731,   727,   730,
     734,   733,   736,   737,   743,   744,   831,   745,   746,   747,
     748,   749,   750,   764,   575,   763,   767,   766,   770,   758,
     769,   772,   773,   774,   775,   781,   782,   821,   822,   830,
     825,   761,   824,   873,   877,   450,   843,   777,   778,   844,
     780,   779,   814,   815,   852,   854,   816,   817,   818,   819,
     879,   883,   881,   901,   837,   838,   902,   903,   906,   839,
     540,   606,   424,   840,   841,   611,   848,   849,   638,   850,
     455,   853,   783,   878,   810,   813,   907,   812,   820,   508,
     785,   784,   809,   482,   631,   857,   786,   787,   882,   501,
     788,   623,   911,   256,   170,   908,   795,   236,   257,   909,
     255,   789,   827,   790,   171,   826,   187,   505,   829,   484,
     270,   189,   828,   791,   250,   802,   493,   696,   823,   190,
     803,   771,   251,   258,   871,   172,   192,   193,   804,   693,
     197,   194,   173,   212,   792,   805,   806,   174,   880,   899,
     807,   793,   198,   523,     0,   213,   794,   202,   910,     0,
       0,     0,     0,     0,     0,   203,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   217,   218,     0,     0,     0,
     219,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   795,     0,     0,     0,
       0,     0,     0,   790,     0,     0,     0,     0,     0,   865,
       0,     0,     0,   791,     0,   802,   864,     0,     0,     0,
     803,     0,     0,     0,     0,     0,   865,     0,   804,     0,
       0,     0,     0,   864,   792,   805,   806,     0,     0,     0,
     807,   793,     0,     0,     0,     0,   794
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    68,    65,    66,    67,    70,    69,    70,    71,
      72,    60,   544,    65,    10,    65,    66,    67,    15,   735,
      65,    66,   735,     5,    69,     7,     7,     9,    65,    66,
     735,    70,    69,     7,    65,    65,    65,    67,    67,   735,
      65,    65,    67,     7,    14,    15,    65,    21,    22,    23,
      24,   119,   120,   121,   122,     3,    22,    23,    24,     0,
       8,    89,    90,     7,     7,     7,    52,     3,    42,    43,
      44,     3,     8,    47,    48,    49,     8,    51,    21,    22,
      23,    24,   150,     7,    50,    51,    52,     7,    62,     7,
      64,    65,    66,    67,    68,    69,    70,    71,     7,    42,
      43,    44,     7,    46,    78,    79,    12,    13,    51,    52,
      16,    77,    86,    19,    78,    72,    73,    74,     3,   147,
     117,    64,    65,     8,    67,     3,     3,   123,    71,   845,
       8,     8,   845,     7,    51,    78,   132,   133,   134,   125,
     845,   127,   128,    86,     7,    11,    63,    64,    65,   845,
       3,   147,     7,     6,    20,    21,    22,    23,    24,    25,
      26,   147,    89,    90,   147,   147,   148,   149,   150,    27,
       3,     3,     6,   147,     6,     8,    42,    43,    44,    45,
      46,   147,    17,    18,    50,    51,    22,    23,    24,    28,
      29,    30,    31,    50,    52,    61,    54,    55,    64,    65,
      58,    59,    60,   735,   147,     3,    64,    65,   740,    75,
      76,     3,   100,   101,     6,    51,    92,    93,    94,    95,
      96,    97,    88,     4,     8,    91,    80,    81,    82,    83,
     147,    85,    98,    99,   126,     3,   102,   129,   130,   131,
      76,     4,     4,     4,    80,    81,    82,    83,    84,    85,
       3,    87,     4,     6,     4,   317,     3,    27,   307,   308,
       4,     8,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    52,    53,    54,    55,    56,    57,     4,     3,
       3,   147,    52,   352,     8,     8,   352,     3,     3,   147,
     352,     3,     8,     8,     3,     3,     8,     4,     3,     8,
       8,     3,   352,     8,   366,     3,     8,   369,     4,     4,
       8,   147,     3,   845,   366,     3,   366,     8,   380,   369,
       8,   366,   352,   352,   369,     4,   395,   352,   390,   366,
     380,   395,   369,   395,     3,   366,   366,   366,     8,     8,
       3,   366,   366,     8,     4,   390,     4,   366,     3,     8,
     380,   380,   414,   390,     4,   380,   395,     4,     3,     8,
       4,     4,     4,     4,     4,     4,     4,   147,   147,     4,
       4,     4,   421,   422,   423,     4,     4,   147,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,     4,   442,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     4,   150,   150,     4,
       4,     4,     4,   148,   148,   148,   148,     4,     4,     4,
       4,     4,   147,     4,     4,     4,     4,     4,   148,     4,
       4,     4,     4,     4,     4,     4,   150,     4,     4,     4,
       4,     4,   148,     4,     4,     4,   150,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   507,     4,
       4,   148,     4,     4,   150,   534,   535,     4,   150,   150,
       4,     4,   534,   535,   150,   524,     4,     4,     4,     4,
     148,   148,   148,     4,     4,     4,   548,     4,   150,   150,
     559,     7,     7,   559,   150,     7,   147,   559,     7,   147,
       7,   147,     5,     5,     5,     5,     3,     5,     7,   559,
       5,     5,     8,     3,     7,     7,     7,     5,     5,     5,
     147,   147,   147,   147,   147,   147,   147,     7,   147,   559,
     559,   147,   147,   147,   559,   124,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,     7,
     147,   147,     7,     7,     7,     7,   118,     4,     7,     7,
       4,     4,     4,    87,     4,     4,   148,     3,     6,     6,
       3,     6,     6,     3,     6,     3,     5,     4,     4,     4,
       4,     4,     4,     3,   485,     6,     3,     6,     4,   147,
       8,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   147,     6,     4,     4,   344,     8,   150,   148,     8,
     148,   150,   148,   148,     8,     7,   148,   148,   148,   148,
       4,     7,     5,     4,   147,   147,     4,     4,     4,   147,
     441,   525,   317,   147,   147,   530,   147,   147,   535,   147,
     350,   147,   723,   148,   738,   744,   150,   742,   751,   398,
     728,   726,   737,   366,   723,   845,   729,   731,   147,   390,
     732,   723,   147,   732,   726,   148,   735,   729,   732,   148,
     732,   734,   764,   735,   726,   762,   726,   395,   767,   369,
     742,   726,   765,   735,   729,   735,   380,   559,   755,   726,
     735,   709,   729,   732,   859,   726,   726,   726,   735,   548,
     762,   726,   726,   765,   735,   735,   735,   726,   875,   887,
     735,   735,   762,   414,    -1,   765,   735,   762,   904,    -1,
      -1,    -1,    -1,    -1,    -1,   762,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   765,   765,    -1,    -1,    -1,
     765,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   845,    -1,    -1,    -1,
      -1,    -1,    -1,   845,    -1,    -1,    -1,    -1,    -1,   858,
      -1,    -1,    -1,   845,    -1,   845,   858,    -1,    -1,    -1,
     845,    -1,    -1,    -1,    -1,    -1,   875,    -1,   845,    -1,
      -1,    -1,    -1,   875,   845,   845,   845,    -1,    -1,    -1,
     845,   845,    -1,    -1,    -1,    -1,   845
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
     199,   200,   203,   205,   208,   211,     7,    47,    48,    49,
      62,    66,    67,    68,    69,    70,    71,    78,    79,    86,
     180,   191,   192,   193,   196,   279,   280,   281,   283,   285,
     287,   289,   291,   293,   295,   298,   299,   334,   352,   364,
     366,   368,   379,   381,   383,   401,    63,   180,   334,   360,
     361,   362,   364,   366,    76,    80,    81,    82,    83,    84,
      85,    87,   180,   334,   376,   377,   378,   379,   381,   383,
     385,   387,   389,   391,   393,   395,   397,   399,   308,    27,
      52,    54,    55,    58,    59,    60,   180,   228,   318,   319,
     320,   321,   322,   323,   324,   326,   328,   330,   331,   333,
     364,   366,    53,    56,    57,   180,   228,   322,   328,   342,
     343,   344,   345,   346,   348,   349,   350,   351,    89,    90,
     180,   255,   256,   257,   259,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   180,
     428,   429,   430,   431,   433,   435,   436,   438,   439,   440,
     443,   445,   446,   447,   448,   451,     6,     3,     4,     8,
       3,   186,   460,   454,   456,   458,     4,     3,     8,   198,
       4,     4,   380,   382,   384,   213,   215,     4,     4,     4,
       4,   272,   309,   335,   301,   365,   367,   239,   406,   248,
     262,     4,   417,   425,     3,     8,   204,   206,   209,     4,
       3,     8,   408,   284,   286,   288,   353,   282,   290,   292,
       4,     4,   296,   294,   369,   402,     3,     8,   363,     3,
       8,   400,   388,   390,   394,   392,   398,   396,   386,     8,
       3,     8,   325,   229,     4,   329,   327,   332,     4,     8,
       3,   347,     4,     4,     8,     3,   258,   260,     3,     8,
       4,   432,   434,     4,   437,     4,     4,   441,   444,     4,
       4,     4,   449,   452,     3,     8,   165,   165,   147,     4,
       4,     4,     4,     4,   184,     4,   150,   150,     4,     4,
       4,     4,     4,   148,   148,   148,   148,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   148,     4,     4,
     190,     4,     4,     4,   150,   200,    77,   180,   228,   308,
     334,   379,   381,   383,   409,   410,   411,   412,   413,     4,
       4,     4,     4,     4,     4,     4,   148,   150,     4,     4,
       4,     4,   280,     4,   361,     4,     4,     4,     4,     4,
       4,     4,     4,   378,     4,     4,   148,     4,     4,     4,
     150,   320,     4,   150,   150,   344,     4,     4,   256,   150,
       4,     4,   148,     4,   148,   148,     4,     4,   150,   150,
     150,     4,     4,   429,     4,     7,     7,   165,   165,   165,
       7,   147,   147,   147,     7,     7,     5,     5,     5,     5,
     167,   169,   165,     5,     5,     5,     7,     7,     7,     5,
     176,    14,    15,   207,    17,    18,   210,   414,     8,     3,
     147,   147,   147,     5,   147,   147,   147,    72,    73,    74,
     297,   147,     5,     7,   147,   176,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     165,   147,   147,   147,    15,   117,   442,   118,   119,   120,
     121,   122,   150,   450,   147,   165,   189,   124,   461,   462,
     463,   199,    27,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,   180,   216,   217,   218,   221,   223,   225,
     227,   228,   230,   231,   232,   233,   234,   236,   216,     7,
     273,   274,   275,     7,   312,   313,   314,     7,   336,   337,
     338,     7,   302,   303,   304,    80,    81,    82,    83,    85,
     240,   241,   242,   243,   244,   245,   246,   293,   407,     7,
     249,   250,   251,    92,    93,    94,    95,    96,    97,   263,
     264,   265,   266,   267,   268,   269,   270,   100,   101,   418,
     419,   420,   422,   428,   177,     4,   411,     7,   354,   355,
     356,     7,   370,   371,   372,    87,   403,     8,   464,     3,
       8,     8,   219,   222,   224,   226,     4,     4,     4,     4,
       4,   235,   237,     3,     8,     8,   276,     6,     3,   315,
       6,     3,   339,     6,     3,   305,     6,     3,     3,     6,
       3,     6,   252,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   421,   423,     3,     8,     8,   147,   178,
     179,   147,   357,     6,     3,   373,     6,     3,   404,     8,
       4,   462,     4,     4,     4,     4,   148,   150,   148,   150,
     148,     4,     4,   217,   279,   275,   318,   314,   342,   338,
     180,   191,   192,   193,   196,   228,   271,   289,   293,   295,
     306,   307,   334,   364,   366,   379,   381,   383,   401,   304,
     241,   293,   255,   251,   148,   148,   148,   148,   148,   148,
     264,     4,     4,   419,     6,     3,   360,   356,   376,   372,
       4,     5,    28,    29,    30,    31,   220,   147,   147,   147,
     147,   147,     8,     8,     8,     3,     8,     8,   147,   147,
     147,     8,     8,   147,     7,   465,   466,   307,   467,     3,
       6,   125,   127,   128,   180,   228,   468,   469,   470,   471,
     473,   466,   474,     4,   472,     3,     8,     4,   148,     4,
     469,     5,   147,     7,   475,   476,   477,     3,     6,   126,
     129,   130,   131,   478,   479,   480,   482,   483,   484,   476,
     481,     4,     4,     4,     3,     8,     4,   150,   148,   148,
     479,   147
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
     202,   201,   204,   203,   206,   205,   207,   207,   209,   208,
     210,   210,   211,   213,   212,   215,   214,   216,   216,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   219,   218,   220,   220,   220,   220,   222,   221,
     224,   223,   226,   225,   227,   229,   228,   230,   231,   232,
     233,   235,   234,   237,   236,   239,   238,   240,   240,   241,
     241,   241,   241,   241,   242,   243,   244,   245,   246,   248,
     247,   249,   249,   250,   250,   252,   251,   254,   253,   255,
     255,   255,   256,   256,   258,   257,   260,   259,   262,   261,
     263,   263,   264,   264,   264,   264,   264,   264,   265,   266,
     267,   268,   269,   270,   272,   271,   273,   273,   274,   274,
     276,   275,   278,   277,   279,   279,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     282,   281,   284,   283,   286,   285,   288,   287,   290,   289,
     292,   291,   294,   293,   296,   295,   297,   297,   297,   298,
     299,   301,   300,   302,   302,   303,   303,   305,   304,   306,
     306,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   309,   308,
     311,   310,   312,   312,   313,   313,   315,   314,   317,   316,
     318,   318,   319,   319,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   321,   322,   323,   325,   324,   327,
     326,   329,   328,   330,   332,   331,   333,   335,   334,   336,
     336,   337,   337,   339,   338,   341,   340,   342,   342,   343,
     343,   344,   344,   344,   344,   344,   344,   344,   345,   347,
     346,   348,   349,   350,   351,   353,   352,   354,   354,   355,
     355,   357,   356,   359,   358,   360,   360,   361,   361,   361,
     361,   361,   363,   362,   365,   364,   367,   366,   369,   368,
     370,   370,   371,   371,   373,   372,   375,   374,   376,   376,
     377,   377,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   380,   379,   382,   381,   384,
     383,   386,   385,   388,   387,   390,   389,   392,   391,   394,
     393,   396,   395,   398,   397,   400,   399,   402,   401,   404,
     403,   406,   405,   407,   407,   408,   293,   409,   409,   410,
     410,   411,   411,   411,   411,   411,   411,   411,   411,   412,
     414,   413,   415,   417,   416,   418,   418,   419,   419,   421,
     420,   423,   422,   425,   424,   427,   426,   428,   428,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   430,   432,   431,   434,   433,   435,
     437,   436,   438,   439,   441,   440,   442,   442,   444,   443,
     445,   446,   447,   449,   448,   450,   450,   450,   450,   450,
     452,   451,   454,   453,   456,   455,   458,   457,   460,   459,
     461,   461,   462,   464,   463,   465,   465,   467,   466,   468,
     468,   469,   469,   469,   469,   469,   470,   472,   471,   474,
     473,   475,   475,   477,   476,   478,   478,   479,   479,   479,
     479,   481,   480,   482,   483,   484
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
       0,     4,     0,     4,     0,     4,     1,     1,     0,     4,
       1,     1,     3,     0,     6,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     3,     0,     4,     0,
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
     493,   493,   502,   502,   512,   512,   519,   520,   523,   523,
     530,   532,   536,   542,   542,   554,   554,   566,   567,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   585,   585,   592,   593,   594,   595,   598,   598,
     606,   606,   614,   614,   622,   627,   627,   635,   640,   645,
     650,   655,   655,   663,   663,   672,   672,   682,   683,   686,
     687,   688,   689,   690,   693,   698,   703,   708,   713,   718,
     718,   728,   729,   732,   733,   736,   736,   746,   746,   756,
     757,   758,   761,   762,   765,   765,   773,   773,   781,   781,
     792,   793,   796,   797,   798,   799,   800,   801,   804,   809,
     814,   819,   824,   829,   837,   837,   850,   851,   854,   855,
     862,   862,   888,   888,   899,   900,   904,   905,   906,   907,
     908,   909,   910,   911,   912,   913,   914,   915,   916,   917,
     918,   919,   920,   921,   922,   923,   924,   925,   926,   927,
     930,   930,   938,   938,   946,   946,   954,   954,   962,   962,
     970,   970,   978,   978,   986,   986,   993,   994,   995,   998,
    1003,  1010,  1010,  1021,  1022,  1026,  1027,  1030,  1030,  1038,
    1039,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1065,  1065,
    1078,  1078,  1087,  1088,  1091,  1092,  1097,  1097,  1112,  1112,
    1126,  1127,  1130,  1131,  1134,  1135,  1136,  1137,  1138,  1139,
    1140,  1141,  1142,  1143,  1146,  1148,  1153,  1155,  1155,  1163,
    1163,  1171,  1171,  1179,  1181,  1181,  1189,  1198,  1198,  1210,
    1211,  1216,  1217,  1222,  1222,  1234,  1234,  1246,  1247,  1252,
    1253,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1267,  1269,
    1269,  1277,  1279,  1281,  1286,  1294,  1294,  1306,  1307,  1310,
    1311,  1314,  1314,  1324,  1324,  1334,  1335,  1338,  1339,  1340,
    1341,  1342,  1345,  1345,  1353,  1353,  1360,  1360,  1372,  1372,
    1382,  1383,  1386,  1387,  1390,  1390,  1399,  1399,  1408,  1409,
    1412,  1413,  1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,
    1425,  1426,  1427,  1428,  1429,  1432,  1432,  1440,  1440,  1448,
    1448,  1456,  1456,  1464,  1464,  1472,  1472,  1480,  1480,  1488,
    1488,  1496,  1496,  1504,  1504,  1512,  1512,  1525,  1525,  1535,
    1535,  1546,  1546,  1556,  1557,  1560,  1560,  1570,  1571,  1574,
    1575,  1578,  1579,  1580,  1581,  1582,  1583,  1584,  1585,  1588,
    1590,  1590,  1602,  1609,  1609,  1619,  1620,  1623,  1624,  1627,
    1627,  1635,  1635,  1645,  1645,  1657,  1657,  1667,  1668,  1671,
    1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1681,
    1682,  1683,  1684,  1685,  1688,  1693,  1693,  1701,  1701,  1709,
    1714,  1714,  1722,  1727,  1732,  1732,  1740,  1741,  1744,  1744,
    1752,  1757,  1762,  1767,  1767,  1775,  1778,  1781,  1784,  1787,
    1793,  1793,  1803,  1803,  1810,  1810,  1817,  1817,  1829,  1829,
    1842,  1843,  1847,  1851,  1851,  1863,  1864,  1868,  1868,  1876,
    1877,  1880,  1881,  1882,  1883,  1884,  1887,  1892,  1892,  1900,
    1900,  1910,  1911,  1914,  1914,  1922,  1923,  1926,  1927,  1928,
    1929,  1932,  1932,  1940,  1945,  1950
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
#line 4409 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1955 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
