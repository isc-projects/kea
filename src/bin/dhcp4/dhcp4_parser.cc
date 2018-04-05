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
      case 166: // value
      case 170: // map_value
      case 208: // socket_type
      case 211: // outbound_interface_value
      case 221: // db_type
      case 300: // hr_mode
      case 445: // ncr_protocol_value
      case 453: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 151: // "boolean"
        value.move< bool > (that.value);
        break;

      case 150: // "floating point"
        value.move< double > (that.value);
        break;

      case 149: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 148: // "constant string"
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
      case 166: // value
      case 170: // map_value
      case 208: // socket_type
      case 211: // outbound_interface_value
      case 221: // db_type
      case 300: // hr_mode
      case 445: // ncr_protocol_value
      case 453: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 151: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 150: // "floating point"
        value.copy< double > (that.value);
        break;

      case 149: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 148: // "constant string"
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
            case 148: // "constant string"

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 149: // "integer"

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 150: // "floating point"

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 151: // "boolean"

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 166: // value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 170: // map_value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 208: // socket_type

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 211: // outbound_interface_value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 221: // db_type

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 300: // hr_mode

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 445: // ncr_protocol_value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 453: // replace_client_name_value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 166: // value
      case 170: // map_value
      case 208: // socket_type
      case 211: // outbound_interface_value
      case 221: // db_type
      case 300: // hr_mode
      case 445: // ncr_protocol_value
      case 453: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 151: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 150: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 149: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 148: // "constant string"
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
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 807 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 268 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 279 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 290 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 862 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 312 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 334 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 945 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 360 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 384 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 403 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 445 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 450 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 460 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 476 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 492 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 501 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 506 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 518 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1168 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 584 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 586 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 591 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 615 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1333 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1369 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 676 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 717 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1499 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 735 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 774 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 803 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1613 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1631 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1669 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 841 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 861 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 865 "dhcp4_parser.yy" // lalr1.cc:859
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

  case 220:
#line 887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1832 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("required-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 990 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1903 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1012 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1024 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1971 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1073 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1124 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2052 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1154 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2061 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1161 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1169 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1177 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1204 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1228 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1232 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1240 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1244 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1305 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1330 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1334 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2322 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1370 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1432 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2443 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2515 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2523 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2541 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2609 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2617 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2638 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2723 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1633 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1744 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2928 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2956 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2965 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1788 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3023 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3031 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1807 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3049 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3058 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3092 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3103 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3112 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1860 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3150 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3159 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1898 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3215 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1936 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3223 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3260 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3264 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -684;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     214,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,    32,    18,    27,    58,    73,    75,    95,
      97,   131,   133,   155,   173,   175,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
      18,  -106,     2,    24,   217,   109,    33,   119,   143,   132,
     156,   -38,   179,  -684,   193,   203,   212,   210,   232,  -684,
    -684,  -684,  -684,  -684,   234,  -684,    52,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,   242,   258,  -684,  -684,  -684,  -684,
    -684,   275,   278,   293,   308,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,   313,  -684,  -684,  -684,    68,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,   320,    80,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
     326,   333,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,    92,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   112,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,   334,   340,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,   336,  -684,  -684,   341,
    -684,  -684,  -684,   342,  -684,  -684,   354,   345,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   359,
     360,  -684,  -684,  -684,  -684,   357,   363,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,   126,  -684,  -684,
    -684,   366,  -684,  -684,   367,  -684,   368,   369,  -684,  -684,
     370,   371,   372,  -684,  -684,  -684,   229,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,    18,    18,  -684,   230,   373,   375,   376,
     377,   378,  -684,     2,  -684,   379,   233,   235,   381,   383,
     384,   385,   386,   243,   244,   245,   246,   387,   392,   393,
     394,   395,   396,   397,   398,   254,   400,   401,    24,  -684,
     402,   403,   404,   259,   217,  -684,   405,   407,   408,   409,
     410,   411,   412,   413,   271,   268,   414,   417,   418,   419,
     420,   109,  -684,   421,    33,  -684,   422,   423,   424,   425,
     426,   427,   428,   429,  -684,   119,  -684,   430,   431,   287,
     433,   434,   435,   290,  -684,   132,   438,   292,   294,  -684,
     156,   440,   442,   -18,  -684,   299,   445,   447,   303,   449,
     307,   309,   455,   456,   310,   311,   312,   460,   462,   179,
    -684,  -684,  -684,   463,   461,   464,    18,    18,    18,  -684,
     465,  -684,  -684,   321,   322,   325,   467,   468,  -684,  -684,
    -684,  -684,   471,   472,   473,   474,   475,   476,   477,   478,
    -684,   479,   480,  -684,   483,    79,   302,  -684,  -684,   335,
     343,   344,   484,   486,   346,   347,   348,  -684,  -684,   236,
     483,   349,   485,   491,  -684,   351,  -684,   483,   352,   353,
     355,   356,   358,   361,   362,  -684,   364,   365,  -684,   374,
     380,   382,  -684,  -684,   388,  -684,  -684,  -684,   389,    18,
    -684,  -684,   390,   391,  -684,   399,  -684,  -684,    21,   406,
    -684,  -684,  -684,   -59,   415,  -684,    18,    24,   416,  -684,
    -684,  -684,   217,  -684,  -684,  -684,   187,   187,   495,   498,
     500,   501,   166,   504,   507,   147,   239,   179,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   508,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,   509,   432,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,   250,  -684,   253,  -684,  -684,
     256,  -684,  -684,  -684,  -684,   513,   514,   515,   517,   519,
    -684,  -684,  -684,   257,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,   260,  -684,   518,
     481,  -684,  -684,   520,   524,  -684,  -684,   523,   528,  -684,
    -684,   526,   530,  -684,  -684,  -684,  -684,  -684,  -684,    48,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,   122,  -684,  -684,
     529,   531,  -684,   536,   538,   539,   540,   541,   542,   263,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   266,
    -684,  -684,  -684,   267,   436,  -684,   543,   545,  -684,  -684,
     544,   548,  -684,  -684,   546,  -684,   549,   416,  -684,  -684,
     551,   552,   553,   554,   437,   439,   443,   444,   448,   555,
     556,   187,  -684,  -684,   109,  -684,   495,   132,  -684,   498,
     156,  -684,   500,    35,  -684,   501,   166,  -684,    67,   504,
    -684,   -38,  -684,   507,   450,   451,   452,   453,   454,   457,
     147,  -684,   557,   558,   239,  -684,  -684,  -684,   559,   561,
      33,  -684,   508,   119,  -684,   509,   562,  -684,   547,  -684,
     118,   441,   446,   459,  -684,  -684,  -684,  -684,  -684,   466,
     469,  -684,   269,  -684,   560,  -684,   563,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   270,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   565,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,   564,   567,  -684,
    -684,  -684,  -684,  -684,   273,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,   470,   482,  -684,  -684,   487,   295,  -684,
     566,  -684,   488,   568,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,    35,  -684,   569,
     458,  -684,    67,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,   158,  -684,  -684,   489,  -684,  -684,    69,   568,  -684,
    -684,  -684,   572,  -684,  -684,  -684,   297,  -684,  -684,  -684,
    -684,  -684,   573,   494,   574,    69,  -684,   575,  -684,   490,
    -684,   576,  -684,  -684,   228,  -684,   -24,   576,  -684,  -684,
     577,   578,   581,   298,  -684,  -684,  -684,  -684,  -684,  -684,
     583,   496,   506,   511,   -24,  -684,   492,  -684,  -684,  -684,
    -684,  -684
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   108,     9,   220,    11,   370,    13,   392,    15,
     299,    17,   307,    19,   342,    21,   185,    23,   473,    25,
      43,    37,     0,     0,     0,     0,     0,   394,     0,   309,
     344,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     526,   520,   522,   524,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   100,     0,     0,   411,   413,   415,   121,
     123,     0,     0,     0,     0,   212,   297,   334,   271,   163,
     437,   177,   196,     0,   461,   471,    93,     0,    68,    70,
      71,    72,    73,    88,    89,    76,    77,    78,    79,    83,
      84,    74,    75,    81,    82,    90,    91,    92,    80,    85,
      86,    87,   110,   112,   116,     0,     0,   102,   104,   105,
     106,   107,   250,   252,   254,   362,   382,   248,   256,   258,
       0,     0,   264,   262,   260,   384,   433,   247,   224,   225,
     226,   239,     0,   222,   229,   243,   244,   245,   230,   231,
     234,   235,   237,   232,   233,   227,   228,   246,   236,   240,
     241,   242,   238,   380,   379,   376,   377,   375,     0,   372,
     374,   378,   431,   419,   421,   425,   423,   429,   427,   417,
     410,   406,     0,   395,   396,   407,   408,   409,   403,   398,
     404,   400,   401,   402,   405,   399,     0,   324,   153,     0,
     328,   326,   331,     0,   320,   321,     0,   310,   311,   313,
     323,   314,   315,   316,   330,   317,   318,   319,   356,     0,
       0,   354,   355,   358,   359,     0,   345,   346,   348,   349,
     350,   351,   352,   353,   192,   194,   189,     0,   187,   190,
     191,     0,   493,   495,     0,   498,     0,     0,   502,   506,
       0,     0,     0,   511,   518,   491,     0,   475,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,    42,     0,     0,    35,     0,     0,     0,     0,
       0,     0,    53,     0,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   221,     0,     0,   371,     0,     0,     0,     0,
       0,     0,     0,     0,   393,     0,   300,     0,     0,     0,
       0,     0,     0,     0,   308,     0,     0,     0,     0,   343,
       0,     0,     0,     0,   186,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     474,    46,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    98,    99,     0,     0,     0,     0,     0,    94,    95,
      96,    97,     0,     0,     0,     0,     0,     0,     0,     0,
     460,     0,     0,    69,     0,     0,     0,   120,   103,     0,
       0,     0,     0,     0,     0,     0,     0,   269,   270,     0,
       0,     0,     0,     0,   223,     0,   373,     0,     0,     0,
       0,     0,     0,     0,     0,   397,     0,     0,   322,     0,
       0,     0,   333,   312,     0,   360,   361,   347,     0,     0,
     188,   492,     0,     0,   497,     0,   500,   501,     0,     0,
     508,   509,   510,     0,     0,   476,     0,     0,     0,   521,
     523,   525,     0,   412,   414,   416,     0,     0,   214,   301,
     336,   273,     0,     0,   179,     0,     0,     0,    47,   111,
     114,   115,   113,   118,   119,   117,   251,   253,   255,   364,
      36,   383,   249,   257,   259,   266,   267,   268,   265,   263,
     261,   386,     0,   381,   432,   420,   422,   426,   424,   430,
     428,   418,   325,   154,   329,   327,   332,   357,   193,   195,
     494,   496,   499,   504,   505,   503,   507,   513,   514,   515,
     516,   517,   512,   519,    40,     0,   531,     0,   528,   530,
       0,   140,   146,   148,   150,     0,     0,     0,     0,     0,
     159,   161,   139,     0,   125,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,     0,   218,     0,
     215,   216,   305,     0,   302,   303,   340,     0,   337,   338,
     277,     0,   274,   275,   172,   173,   174,   175,   176,     0,
     165,   167,   168,   169,   170,   171,   441,     0,   439,   183,
       0,   180,   181,     0,     0,     0,     0,     0,     0,     0,
     198,   200,   201,   202,   203,   204,   205,   467,   469,     0,
     463,   465,   466,     0,    49,   368,     0,   365,   366,   390,
       0,   387,   388,   435,     0,    65,     0,     0,   527,   101,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   122,   124,     0,   213,     0,   309,   298,     0,
     344,   335,     0,     0,   272,     0,     0,   164,   443,     0,
     438,     0,   178,     0,     0,     0,     0,     0,     0,     0,
       0,   197,     0,     0,     0,   462,   472,    51,     0,    50,
       0,   363,     0,   394,   385,     0,     0,   434,     0,   529,
       0,     0,     0,     0,   152,   155,   156,   157,   158,     0,
       0,   126,     0,   217,     0,   304,     0,   339,   296,   295,
     284,   285,   287,   281,   282,   283,   293,   294,   292,     0,
     279,   286,   288,   289,   290,   291,   276,   166,   457,     0,
     455,   456,   450,   451,   452,   453,   454,     0,   444,   445,
     447,   448,   449,   440,     0,   182,   206,   207,   208,   209,
     210,   211,   199,     0,     0,   464,    48,     0,     0,   367,
       0,   389,     0,     0,   142,   143,   144,   145,   141,   147,
     149,   151,   160,   162,   219,   306,   341,     0,   278,     0,
       0,   442,     0,   184,   468,   470,    52,   369,   391,   436,
     535,     0,   533,   280,     0,   459,   446,     0,     0,   532,
     458,   547,     0,   545,   543,   539,     0,   537,   541,   542,
     540,   534,     0,     0,     0,     0,   536,     0,   544,     0,
     538,     0,   546,   551,     0,   549,     0,     0,   548,   559,
       0,     0,     0,     0,   553,   555,   556,   557,   558,   550,
       0,     0,     0,     0,     0,   552,     0,   561,   562,   563,
     554,   560
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,   -49,  -684,   114,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -447,  -684,  -684,  -684,   -62,
    -684,  -684,  -684,   280,  -684,  -684,  -684,  -684,    72,   272,
     -51,   -28,   -27,  -684,  -684,   -22,  -684,  -684,    76,   247,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,    81,  -105,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,   -69,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -112,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -118,  -684,  -684,  -684,  -113,   218,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -117,  -684,  -684,  -684,  -684,  -684,  -684,
    -683,  -684,  -684,  -684,   -94,  -684,  -684,  -684,   -89,   255,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -682,  -684,
    -684,  -684,   -33,  -684,   -26,  -684,  -674,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,   -96,  -684,  -684,  -217,   -66,
    -684,  -684,  -684,  -684,  -684,   -88,  -684,  -684,  -684,   -85,
    -684,   238,  -684,   -64,  -684,  -684,  -684,  -684,  -684,   -41,
    -684,  -684,  -684,  -684,  -684,   -50,  -684,  -684,  -684,   -87,
    -684,  -684,  -684,   -86,  -684,   237,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -116,  -684,  -684,
    -684,  -111,   264,  -684,  -684,   -48,  -684,  -684,  -684,  -684,
    -684,  -114,  -684,  -684,  -684,  -110,  -684,   282,   -46,  -684,
     -43,  -684,   -39,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -672,  -684,  -684,  -684,  -684,  -684,  -684,   -55,  -684,  -684,
    -684,  -208,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
     -84,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,   139,
     262,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,  -684,
    -684,  -684,  -684,   -14,  -684,  -684,  -684,  -175,  -684,  -684,
    -191,  -684,  -684,  -684,  -684,  -684,  -684,  -199,  -684,  -684,
    -215,  -684,  -684,  -684,  -684,  -684
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   541,    77,
      78,    37,    60,    74,    75,   529,   674,   738,   739,   116,
      39,    62,    86,    87,    88,   307,    41,    63,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   315,   146,   147,
      43,    64,   148,   340,   149,   341,   532,   150,   342,   535,
     151,   126,   321,   127,   322,   603,   604,   605,   690,   828,
     606,   691,   607,   692,   608,   693,   609,   235,   378,   611,
     612,   613,   614,   615,   699,   616,   700,   128,   331,   639,
     640,   641,   642,   643,   644,   645,   129,   333,   650,   651,
     652,   721,    57,    71,   267,   268,   269,   391,   270,   392,
     130,   334,   659,   660,   661,   662,   663,   664,   665,   666,
     131,   327,   619,   620,   621,   704,    45,    65,   172,   173,
     174,   351,   175,   346,   176,   347,   177,   348,   178,   352,
     179,   353,   180,   358,   181,   357,   182,   356,   548,   183,
     184,   132,   330,   631,   632,   633,   713,   779,   780,   133,
     328,    51,    68,   623,   624,   625,   707,    53,    69,   236,
     237,   238,   239,   240,   241,   242,   377,   243,   381,   244,
     380,   245,   246,   382,   247,   134,   329,   627,   628,   629,
     710,    55,    70,   255,   256,   257,   258,   259,   386,   260,
     261,   262,   263,   186,   349,   676,   677,   678,   740,    47,
      66,   198,   199,   200,   363,   187,   350,   188,   359,   680,
     681,   682,   743,    49,    67,   212,   213,   214,   135,   318,
     136,   319,   137,   320,   218,   373,   219,   367,   220,   368,
     221,   370,   222,   369,   223,   372,   224,   371,   225,   366,
     192,   360,   684,   746,   138,   332,   647,   648,   718,   797,
     798,   799,   800,   801,   839,   802,   139,   140,   336,   669,
     670,   671,   732,   672,   733,   141,   337,    59,    72,   286,
     287,   288,   289,   396,   290,   397,   291,   292,   399,   293,
     294,   295,   402,   575,   296,   403,   297,   298,   299,   300,
     407,   582,   301,   408,    89,   309,    90,   310,    91,   311,
      92,   308,   587,   588,   589,   686,   851,   852,   857,   866,
     867,   868,   869,   874,   870,   872,   884,   885,   886,   893,
     894,   895,   900,   896,   897,   898
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   252,   226,   167,   194,   210,   253,   234,   251,   266,
     285,    73,    79,   549,   168,   185,   197,   211,   201,   189,
     554,   215,   190,    27,   216,    28,   191,    29,   217,   254,
     774,   775,    26,   195,    38,    93,   573,   169,   170,   778,
     196,   785,    76,   171,    94,    95,    96,    97,    98,    99,
     100,   716,   264,   265,   717,   313,    95,    96,    97,    98,
     314,   577,   578,   579,   580,    40,   101,   102,   103,   104,
     105,   338,   264,   265,   106,   107,   339,   101,   102,   103,
      42,   105,    44,   344,   107,   108,   107,   228,   345,    96,
      97,    98,   581,   530,   531,   361,   193,   156,   109,   110,
     362,   158,    46,   889,    48,   162,   890,   891,   892,   163,
      84,   163,   164,   111,   164,   364,   112,   106,   107,   228,
     365,   228,   166,   113,   114,   719,    80,   115,   720,   393,
      95,    96,    97,    98,   394,    81,    82,    83,    50,   574,
      52,    96,    97,    98,   788,   789,   824,   825,   826,   827,
      84,   101,   102,   103,   774,   775,   152,   153,   154,   227,
     107,   858,    54,   778,   859,   785,    30,    31,    32,    33,
     107,   155,    84,   156,   157,   158,   159,   160,   161,   162,
      56,    84,    58,    84,   228,   163,   229,   230,   164,   165,
     231,   232,   233,   106,   202,   861,   166,   862,   863,   302,
     203,   204,   205,   206,   207,   208,   303,   209,   228,   248,
     229,   230,   249,   250,   591,    84,   304,    84,   305,   592,
     593,   594,   595,   596,   597,   598,   599,   600,   601,   142,
     143,   887,   409,   144,   888,   306,   145,   410,   312,   228,
     653,   654,   655,   656,   657,   658,   316,   634,   635,   636,
     637,    85,   638,   338,   411,   412,   687,    84,   685,   344,
     701,   688,   317,   701,   689,   702,   730,    84,   703,   734,
     409,   731,   361,   837,   735,   736,   393,   834,   838,   323,
      84,   843,   324,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   325,   364,   167,
     875,   904,   194,   847,    84,   876,   905,   545,   546,   547,
     168,   185,   326,   210,   197,   189,   201,   335,   190,   533,
     534,   252,   191,   234,   343,   211,   253,    84,   251,   215,
     354,   195,   216,   169,   170,    84,   217,   355,   196,   171,
     667,   668,   374,   375,   376,   379,   383,   285,   385,   254,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,   384,   387,   388,   389,   390,   509,   510,   511,
     395,   398,   400,   401,   404,   405,   406,   414,   413,   415,
     416,   417,   418,   420,   421,   423,   422,   424,   425,   426,
     427,   432,   428,   429,   430,   431,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   444,   445,   446,   449,
     447,   450,   451,   452,   453,   454,   455,   456,   459,   458,
     457,   460,   461,   462,   463,   465,   467,   468,   469,   470,
     471,   472,   473,   474,   476,   477,   478,   479,   480,   481,
     569,   482,   484,   485,   488,   486,   489,   610,   610,   492,
     491,   493,   494,   495,   602,   602,   496,   584,   497,   498,
     499,   500,   501,   502,   503,   285,   504,   506,   507,   513,
     514,   508,   512,   515,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   536,   706,   525,   526,   527,   528,   539,
     551,   537,   538,    28,   542,   543,   544,   550,   552,   553,
     555,   556,   618,   557,   558,   622,   559,   626,   630,   560,
     561,   646,   562,   563,   649,   675,   679,   694,   695,   696,
     683,   697,   564,   698,   705,   576,   708,   709,   565,   711,
     566,   712,   714,   715,   723,   722,   567,   568,   570,   571,
     724,   586,   725,   726,   727,   728,   729,   572,   742,   741,
     744,   745,   823,   748,   747,   750,   751,   752,   753,   759,
     760,   813,   814,   583,   817,   816,   822,   540,   835,   840,
     842,   836,   841,   854,   848,   850,   873,   877,   879,   585,
     881,   901,   902,   883,   737,   903,   754,   906,   590,   829,
     755,   448,   756,   419,   830,   757,   761,   758,   617,   806,
     807,   808,   809,   810,   787,   805,   811,   831,   804,   855,
     443,   490,   763,   812,   832,   762,   464,   833,   844,   786,
     853,   765,   764,   483,   766,   767,   819,   487,   466,   818,
     845,   821,   610,   820,   856,   846,   849,   860,   882,   602,
     911,   252,   167,   878,   773,   234,   253,   907,   251,   791,
     815,   768,   792,   168,   185,   908,   790,   475,   189,   266,
     909,   190,   769,   781,   803,   191,   673,   782,   793,   254,
     783,   505,   794,   749,   784,   795,   169,   170,   194,   796,
     776,   210,   171,   871,   880,   770,   771,   777,   899,   910,
     197,   772,   201,   211,     0,     0,     0,   215,     0,     0,
     216,     0,     0,     0,   217,     0,     0,   195,     0,     0,
       0,     0,     0,     0,   196,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   773,     0,
       0,     0,     0,   791,     0,   768,   792,     0,     0,     0,
     790,     0,     0,     0,     0,     0,   769,   781,   865,     0,
       0,   782,   793,     0,   783,   864,   794,     0,   784,   795,
       0,     0,     0,   796,   776,     0,   865,     0,     0,   770,
     771,   777,     0,   864,     0,   772
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    68,    65,    66,    67,    70,    69,    70,    71,
      72,    60,    10,   460,    65,    65,    66,    67,    66,    65,
     467,    67,    65,     5,    67,     7,    65,     9,    67,    70,
     713,   713,     0,    66,     7,    11,    15,    65,    65,   713,
      66,   713,   148,    65,    20,    21,    22,    23,    24,    25,
      26,     3,    90,    91,     6,     3,    21,    22,    23,    24,
       8,   120,   121,   122,   123,     7,    42,    43,    44,    45,
      46,     3,    90,    91,    50,    51,     8,    42,    43,    44,
       7,    46,     7,     3,    51,    61,    51,    52,     8,    22,
      23,    24,   151,    14,    15,     3,    63,    64,    74,    75,
       8,    66,     7,   127,     7,    70,   130,   131,   132,    76,
     148,    76,    79,    89,    79,     3,    92,    50,    51,    52,
       8,    52,    87,    99,   100,     3,   124,   103,     6,     3,
      21,    22,    23,    24,     8,   133,   134,   135,     7,   118,
       7,    22,    23,    24,    77,    78,    28,    29,    30,    31,
     148,    42,    43,    44,   837,   837,    47,    48,    49,    27,
      51,     3,     7,   837,     6,   837,   148,   149,   150,   151,
      51,    62,   148,    64,    65,    66,    67,    68,    69,    70,
       7,   148,     7,   148,    52,    76,    54,    55,    79,    80,
      58,    59,    60,    50,    75,   126,    87,   128,   129,     6,
      81,    82,    83,    84,    85,    86,     3,    88,    52,    53,
      54,    55,    56,    57,    27,   148,     4,   148,     8,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    12,
      13,     3,     3,    16,     6,     3,    19,     8,     4,    52,
      93,    94,    95,    96,    97,    98,     4,    81,    82,    83,
      84,   313,    86,     3,   303,   304,     3,   148,     8,     3,
       3,     8,     4,     3,     8,     8,     3,   148,     8,     3,
       3,     8,     3,     3,     8,     8,     3,     8,     8,     4,
     148,     8,     4,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,     4,     3,   361,
       3,     3,   364,     8,   148,     8,     8,    71,    72,    73,
     361,   361,     4,   375,   364,   361,   364,     4,   361,    17,
      18,   390,   361,   385,     4,   375,   390,   148,   390,   375,
       4,   364,   375,   361,   361,   148,   375,     4,   364,   361,
     101,   102,     8,     3,     8,     4,     4,   409,     3,   390,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,     8,     4,     4,     8,     3,   416,   417,   418,
       4,     4,     4,     4,     4,     4,     4,     4,   148,     4,
       4,     4,     4,     4,   151,     4,   151,     4,     4,     4,
       4,     4,   149,   149,   149,   149,     4,     4,     4,     4,
       4,     4,     4,   149,     4,     4,     4,     4,     4,     4,
     151,     4,     4,     4,     4,     4,     4,     4,     4,   151,
     149,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   149,     4,     4,     4,
     489,   151,     4,   151,     4,   151,     4,   516,   517,     4,
     151,     4,   149,     4,   516,   517,   149,   506,   149,     4,
       4,   151,   151,   151,     4,   527,     4,     4,     7,   148,
     148,     7,     7,   148,     7,     7,     5,     5,     5,     5,
       5,     5,     5,   148,     3,     7,     7,     7,     5,     5,
       5,   148,   148,     7,   148,   148,   148,   148,     7,   148,
     148,   148,     7,   148,   148,     7,   148,     7,     7,   148,
     148,     7,   148,   148,     7,     7,     7,     4,     4,     4,
      88,     4,   148,     4,     6,   119,     6,     3,   148,     6,
     148,     3,     6,     3,     3,     6,   148,   148,   148,   148,
       4,   125,     4,     4,     4,     4,     4,   148,     3,     6,
       6,     3,     5,     4,     8,     4,     4,     4,     4,     4,
       4,     4,     4,   148,     3,     6,     4,   453,     8,     4,
       3,     8,     8,     4,     8,     7,     4,     4,     4,   507,
       5,     4,     4,     7,   148,     4,   149,     4,   512,   148,
     151,   344,   149,   313,   148,   151,   701,   149,   517,   149,
     149,   149,   149,   149,   716,   723,   149,   148,   721,   151,
     338,   393,   706,   730,   148,   704,   361,   148,   148,   715,
     837,   709,   707,   385,   710,   712,   742,   390,   364,   740,
     148,   745,   701,   743,   842,   148,   148,   148,   148,   701,
     148,   710,   704,   149,   713,   707,   710,   151,   710,   718,
     734,   713,   718,   704,   704,   149,   718,   375,   704,   721,
     149,   704,   713,   713,   719,   704,   527,   713,   718,   710,
     713,   409,   718,   687,   713,   718,   704,   704,   740,   718,
     713,   743,   704,   858,   875,   713,   713,   713,   887,   904,
     740,   713,   740,   743,    -1,    -1,    -1,   743,    -1,    -1,
     743,    -1,    -1,    -1,   743,    -1,    -1,   740,    -1,    -1,
      -1,    -1,    -1,    -1,   740,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   837,    -1,
      -1,    -1,    -1,   842,    -1,   837,   842,    -1,    -1,    -1,
     842,    -1,    -1,    -1,    -1,    -1,   837,   837,   857,    -1,
      -1,   837,   842,    -1,   837,   857,   842,    -1,   837,   842,
      -1,    -1,    -1,   842,   837,    -1,   875,    -1,    -1,   837,
     837,   837,    -1,   875,    -1,   837
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     0,     5,     7,     9,
     148,   149,   150,   151,   166,   167,   168,   173,     7,   182,
       7,   188,     7,   202,     7,   278,     7,   361,     7,   375,
       7,   313,     7,   319,     7,   343,     7,   254,     7,   429,
     174,   169,   183,   189,   203,   279,   362,   376,   314,   320,
     344,   255,   430,   166,   175,   176,   148,   171,   172,    10,
     124,   133,   134,   135,   148,   181,   184,   185,   186,   456,
     458,   460,   462,    11,    20,    21,    22,    23,    24,    25,
      26,    42,    43,    44,    45,    46,    50,    51,    61,    74,
      75,    89,    92,    99,   100,   103,   181,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   213,   215,   239,   248,
     262,   272,   303,   311,   337,   380,   382,   384,   406,   418,
     419,   427,    12,    13,    16,    19,   200,   201,   204,   206,
     209,   212,    47,    48,    49,    62,    64,    65,    66,    67,
      68,    69,    70,    76,    79,    80,    87,   181,   192,   193,
     194,   197,   280,   281,   282,   284,   286,   288,   290,   292,
     294,   296,   298,   301,   302,   337,   355,   367,   369,   380,
     382,   384,   402,    63,   181,   294,   296,   337,   363,   364,
     365,   367,    75,    81,    82,    83,    84,    85,    86,    88,
     181,   337,   377,   378,   379,   380,   382,   384,   386,   388,
     390,   392,   394,   396,   398,   400,   311,    27,    52,    54,
      55,    58,    59,    60,   181,   229,   321,   322,   323,   324,
     325,   326,   327,   329,   331,   333,   334,   336,    53,    56,
      57,   181,   229,   325,   331,   345,   346,   347,   348,   349,
     351,   352,   353,   354,    90,    91,   181,   256,   257,   258,
     260,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   181,   431,   432,   433,   434,
     436,   438,   439,   441,   442,   443,   446,   448,   449,   450,
     451,   454,     6,     3,     4,     8,     3,   187,   463,   457,
     459,   461,     4,     3,     8,   199,     4,     4,   381,   383,
     385,   214,   216,     4,     4,     4,     4,   273,   312,   338,
     304,   240,   407,   249,   263,     4,   420,   428,     3,     8,
     205,   207,   210,     4,     3,     8,   285,   287,   289,   356,
     368,   283,   291,   293,     4,     4,   299,   297,   295,   370,
     403,     3,     8,   366,     3,     8,   401,   389,   391,   395,
     393,   399,   397,   387,     8,     3,     8,   328,   230,     4,
     332,   330,   335,     4,     8,     3,   350,     4,     4,     8,
       3,   259,   261,     3,     8,     4,   435,   437,     4,   440,
       4,     4,   444,   447,     4,     4,     4,   452,   455,     3,
       8,   166,   166,   148,     4,     4,     4,     4,     4,   185,
       4,   151,   151,     4,     4,     4,     4,     4,   149,   149,
     149,   149,     4,     4,     4,     4,     4,     4,     4,     4,
     149,     4,     4,   191,     4,     4,     4,   151,   201,     4,
       4,     4,     4,     4,     4,     4,     4,   149,   151,     4,
       4,     4,     4,     4,   281,     4,   364,     4,     4,     4,
       4,     4,     4,     4,     4,   379,     4,     4,   149,     4,
       4,     4,   151,   323,     4,   151,   151,   347,     4,     4,
     257,   151,     4,     4,   149,     4,   149,   149,     4,     4,
     151,   151,   151,     4,     4,   432,     4,     7,     7,   166,
     166,   166,     7,   148,   148,   148,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     7,     7,     7,     5,   177,
      14,    15,   208,    17,    18,   211,   148,   148,   148,     5,
     168,   170,   148,   148,   148,    71,    72,    73,   300,   177,
     148,     5,     7,   148,   177,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   166,
     148,   148,   148,    15,   118,   445,   119,   120,   121,   122,
     123,   151,   453,   148,   166,   190,   125,   464,   465,   466,
     200,    27,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,   181,   217,   218,   219,   222,   224,   226,   228,
     229,   231,   232,   233,   234,   235,   237,   217,     7,   274,
     275,   276,     7,   315,   316,   317,     7,   339,   340,   341,
       7,   305,   306,   307,    81,    82,    83,    84,    86,   241,
     242,   243,   244,   245,   246,   247,     7,   408,   409,     7,
     250,   251,   252,    93,    94,    95,    96,    97,    98,   264,
     265,   266,   267,   268,   269,   270,   271,   101,   102,   421,
     422,   423,   425,   431,   178,     7,   357,   358,   359,     7,
     371,   372,   373,    88,   404,     8,   467,     3,     8,     8,
     220,   223,   225,   227,     4,     4,     4,     4,     4,   236,
     238,     3,     8,     8,   277,     6,     3,   318,     6,     3,
     342,     6,     3,   308,     6,     3,     3,     6,   410,     3,
       6,   253,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   424,   426,     3,     8,     8,   148,   179,   180,
     360,     6,     3,   374,     6,     3,   405,     8,     4,   465,
       4,     4,     4,     4,   149,   151,   149,   151,   149,     4,
       4,   218,   280,   276,   321,   317,   345,   341,   181,   192,
     193,   194,   197,   229,   272,   290,   294,   296,   298,   309,
     310,   337,   380,   382,   384,   402,   307,   242,    77,    78,
     181,   229,   311,   337,   380,   382,   384,   411,   412,   413,
     414,   415,   417,   409,   256,   252,   149,   149,   149,   149,
     149,   149,   265,     4,     4,   422,     6,     3,   363,   359,
     377,   373,     4,     5,    28,    29,    30,    31,   221,   148,
     148,   148,   148,   148,     8,     8,     8,     3,     8,   416,
       4,     8,     3,     8,   148,   148,   148,     8,     8,   148,
       7,   468,   469,   310,     4,   151,   413,   470,     3,     6,
     148,   126,   128,   129,   181,   229,   471,   472,   473,   474,
     476,   469,   477,     4,   475,     3,     8,     4,   149,     4,
     472,     5,   148,     7,   478,   479,   480,     3,     6,   127,
     130,   131,   132,   481,   482,   483,   485,   486,   487,   479,
     484,     4,     4,     4,     3,     8,     4,   151,   149,   149,
     482,   148
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   152,   154,   153,   155,   153,   156,   153,   157,   153,
     158,   153,   159,   153,   160,   153,   161,   153,   162,   153,
     163,   153,   164,   153,   165,   153,   166,   166,   166,   166,
     166,   166,   166,   167,   169,   168,   170,   171,   171,   172,
     172,   174,   173,   175,   175,   176,   176,   178,   177,   179,
     179,   180,   180,   181,   183,   182,   184,   184,   185,   185,
     185,   185,   185,   185,   187,   186,   189,   188,   190,   190,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   192,   193,   194,   195,   196,   197,
     199,   198,   200,   200,   201,   201,   201,   201,   203,   202,
     205,   204,   207,   206,   208,   208,   210,   209,   211,   211,
     212,   214,   213,   216,   215,   217,   217,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     220,   219,   221,   221,   221,   221,   223,   222,   225,   224,
     227,   226,   228,   230,   229,   231,   232,   233,   234,   236,
     235,   238,   237,   240,   239,   241,   241,   242,   242,   242,
     242,   242,   243,   244,   245,   246,   247,   249,   248,   250,
     250,   251,   251,   253,   252,   255,   254,   256,   256,   256,
     257,   257,   259,   258,   261,   260,   263,   262,   264,   264,
     265,   265,   265,   265,   265,   265,   266,   267,   268,   269,
     270,   271,   273,   272,   274,   274,   275,   275,   277,   276,
     279,   278,   280,   280,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   283,   282,
     285,   284,   287,   286,   289,   288,   291,   290,   293,   292,
     295,   294,   297,   296,   299,   298,   300,   300,   300,   301,
     302,   304,   303,   305,   305,   306,   306,   308,   307,   309,
     309,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   312,   311,   314,
     313,   315,   315,   316,   316,   318,   317,   320,   319,   321,
     321,   322,   322,   323,   323,   323,   323,   323,   323,   323,
     323,   324,   325,   326,   328,   327,   330,   329,   332,   331,
     333,   335,   334,   336,   338,   337,   339,   339,   340,   340,
     342,   341,   344,   343,   345,   345,   346,   346,   347,   347,
     347,   347,   347,   347,   347,   348,   350,   349,   351,   352,
     353,   354,   356,   355,   357,   357,   358,   358,   360,   359,
     362,   361,   363,   363,   364,   364,   364,   364,   364,   364,
     366,   365,   368,   367,   370,   369,   371,   371,   372,   372,
     374,   373,   376,   375,   377,   377,   378,   378,   379,   379,
     379,   379,   379,   379,   379,   379,   379,   379,   379,   379,
     379,   381,   380,   383,   382,   385,   384,   387,   386,   389,
     388,   391,   390,   393,   392,   395,   394,   397,   396,   399,
     398,   401,   400,   403,   402,   405,   404,   407,   406,   408,
     408,   410,   409,   411,   411,   412,   412,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   414,   416,   415,   417,
     418,   420,   419,   421,   421,   422,   422,   424,   423,   426,
     425,   428,   427,   430,   429,   431,   431,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   433,   435,   434,   437,   436,   438,   440,   439,
     441,   442,   444,   443,   445,   445,   447,   446,   448,   449,
     450,   452,   451,   453,   453,   453,   453,   453,   455,   454,
     457,   456,   459,   458,   461,   460,   463,   462,   464,   464,
     465,   467,   466,   468,   468,   470,   469,   471,   471,   472,
     472,   472,   472,   472,   473,   475,   474,   477,   476,   478,
     478,   480,   479,   481,   481,   482,   482,   482,   482,   484,
     483,   485,   486,   487
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
       0,     6,     1,     3,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
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
  "\"subnet\"", "\"interface\"", "\"interface-id\"", "\"id\"",
  "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"required-client-classes\"", "\"test\"",
  "\"only-if-required\"", "\"client-class\"", "\"reservations\"",
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
  "$@48", "client_class", "$@49", "required_client_classes", "$@50",
  "reservation_mode", "$@51", "hr_mode", "id", "rapid_commit",
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
  "not_empty_pools_list", "pool_list_entry", "$@67", "sub_pool4", "$@68",
  "pool_params", "pool_param", "pool_entry", "$@69", "user_context",
  "$@70", "reservations", "$@71", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@72", "sub_reservation",
  "$@73", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@74", "server_hostname", "$@75",
  "boot_file_name", "$@76", "ip_address", "$@77", "duid", "$@78",
  "hw_address", "$@79", "client_id_value", "$@80", "circuit_id_value",
  "$@81", "flex_id_value", "$@82", "hostname", "$@83",
  "reservation_client_classes", "$@84", "relay", "$@85", "relay_map",
  "$@86", "client_classes", "$@87", "client_classes_list",
  "client_class_entry", "$@88", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@89", "only_if_required",
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
       0,   235,   235,   235,   236,   236,   237,   237,   238,   238,
     239,   239,   240,   240,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   245,   246,   246,   254,   255,   256,   257,
     258,   259,   260,   263,   268,   268,   279,   282,   283,   286,
     290,   297,   297,   304,   305,   308,   312,   319,   319,   326,
     327,   330,   334,   345,   355,   355,   371,   372,   376,   377,
     378,   379,   380,   381,   384,   384,   399,   399,   408,   409,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   440,   445,   450,   455,   460,   465,
     471,   471,   482,   483,   486,   487,   488,   489,   492,   492,
     501,   501,   511,   511,   518,   519,   522,   522,   529,   531,
     535,   541,   541,   553,   553,   565,   566,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     584,   584,   591,   592,   593,   594,   597,   597,   605,   605,
     613,   613,   621,   626,   626,   634,   639,   644,   649,   654,
     654,   662,   662,   671,   671,   681,   682,   685,   686,   687,
     688,   689,   692,   697,   702,   707,   712,   717,   717,   727,
     728,   731,   732,   735,   735,   745,   745,   755,   756,   757,
     760,   761,   764,   764,   772,   772,   780,   780,   791,   792,
     795,   796,   797,   798,   799,   800,   803,   808,   813,   818,
     823,   828,   836,   836,   849,   850,   853,   854,   861,   861,
     887,   887,   898,   899,   903,   904,   905,   906,   907,   908,
     909,   910,   911,   912,   913,   914,   915,   916,   917,   918,
     919,   920,   921,   922,   923,   924,   925,   926,   929,   929,
     937,   937,   945,   945,   953,   953,   961,   961,   969,   969,
     977,   977,   985,   985,   995,   995,  1002,  1003,  1004,  1007,
    1012,  1019,  1019,  1030,  1031,  1035,  1036,  1039,  1039,  1047,
    1048,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1073,  1073,  1086,
    1086,  1095,  1096,  1099,  1100,  1105,  1105,  1120,  1120,  1134,
    1135,  1138,  1139,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1152,  1154,  1159,  1161,  1161,  1169,  1169,  1177,  1177,
    1185,  1187,  1187,  1195,  1204,  1204,  1216,  1217,  1222,  1223,
    1228,  1228,  1240,  1240,  1252,  1253,  1258,  1259,  1264,  1265,
    1266,  1267,  1268,  1269,  1270,  1273,  1275,  1275,  1283,  1285,
    1287,  1292,  1300,  1300,  1312,  1313,  1316,  1317,  1320,  1320,
    1330,  1330,  1340,  1341,  1344,  1345,  1346,  1347,  1348,  1349,
    1352,  1352,  1360,  1360,  1370,  1370,  1380,  1381,  1384,  1385,
    1388,  1388,  1397,  1397,  1406,  1407,  1410,  1411,  1415,  1416,
    1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,
    1427,  1430,  1430,  1438,  1438,  1446,  1446,  1454,  1454,  1462,
    1462,  1470,  1470,  1478,  1478,  1486,  1486,  1494,  1494,  1502,
    1502,  1510,  1510,  1523,  1523,  1533,  1533,  1544,  1544,  1554,
    1555,  1558,  1558,  1568,  1569,  1572,  1573,  1576,  1577,  1578,
    1579,  1580,  1581,  1582,  1583,  1584,  1587,  1589,  1589,  1597,
    1606,  1613,  1613,  1623,  1624,  1627,  1628,  1631,  1631,  1639,
    1639,  1649,  1649,  1661,  1661,  1671,  1672,  1675,  1676,  1677,
    1678,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,
    1688,  1689,  1692,  1697,  1697,  1705,  1705,  1713,  1718,  1718,
    1726,  1731,  1736,  1736,  1744,  1745,  1748,  1748,  1756,  1761,
    1766,  1771,  1771,  1779,  1782,  1785,  1788,  1791,  1797,  1797,
    1807,  1807,  1814,  1814,  1821,  1821,  1833,  1833,  1846,  1847,
    1851,  1855,  1855,  1867,  1868,  1872,  1872,  1880,  1881,  1884,
    1885,  1886,  1887,  1888,  1891,  1896,  1896,  1904,  1904,  1914,
    1915,  1918,  1918,  1926,  1927,  1930,  1931,  1932,  1933,  1936,
    1936,  1944,  1949,  1954
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
#line 4420 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1959 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
