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
      case 183: // value
      case 187: // map_value
      case 225: // socket_type
      case 228: // outbound_interface_value
      case 250: // db_type
      case 332: // hr_mode
      case 479: // ncr_protocol_value
      case 487: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 166: // "boolean"
        value.move< bool > (that.value);
        break;

      case 165: // "floating point"
        value.move< double > (that.value);
        break;

      case 164: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 163: // "constant string"
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
      case 183: // value
      case 187: // map_value
      case 225: // socket_type
      case 228: // outbound_interface_value
      case 250: // db_type
      case 332: // hr_mode
      case 479: // ncr_protocol_value
      case 487: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 166: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 165: // "floating point"
        value.copy< double > (that.value);
        break;

      case 164: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 163: // "constant string"
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
            case 163: // "constant string"

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 366 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 164: // "integer"

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 373 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 165: // "floating point"

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 380 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 166: // "boolean"

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 387 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 183: // value

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 187: // map_value

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 225: // socket_type

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 228: // outbound_interface_value

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 250: // db_type

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 332: // hr_mode

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 429 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 479: // ncr_protocol_value

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 487: // replace_client_name_value

#line 242 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 183: // value
      case 187: // map_value
      case 225: // socket_type
      case 228: // outbound_interface_value
      case 250: // db_type
      case 332: // hr_mode
      case 479: // ncr_protocol_value
      case 487: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 166: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 165: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 164: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 163: // "constant string"
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
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 253 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 702 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 254 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 272 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 273 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 275 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 277 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 286 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 297 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 308 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 318 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 882 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 326 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 891 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 330 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 900 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 908 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 339 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 917 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 348 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 926 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 352 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 935 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 378 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 469 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1039 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 484 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 533 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1126 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1134 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 540 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 545 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 546 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1155 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1188 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1197 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 568 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1219 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 580 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    {

    if ( (string(yystack_[0].value.as< std::string > ()) == "none") ||
         (string(yystack_[0].value.as< std::string > ()) == "warn") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as< std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as< std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1278 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1289 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1337 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1346 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 684 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1352 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 686 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 687 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 706 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1414 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1424 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 719 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 727 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 732 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 737 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1478 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1496 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1532 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1550 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1579 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 793 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1597 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1606 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1615 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1624 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1633 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1653 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 852 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1663 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1673 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 224:
#line 866 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 230:
#line 881 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 231:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 232:
#line 889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 233:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 902 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1749 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1767 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 930 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 982 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 1004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1869 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 1008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1045 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1053 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1055 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1061 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 290:
#line 1063 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 291:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 292:
#line 1071 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1079 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1085 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1087 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1093 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1103 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1105 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1116 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2057 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2106 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1195 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1211 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1215 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1230 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2176 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2185 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2193 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2203 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1279 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2229 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1287 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1297 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1312 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2277 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1317 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1336 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2315 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2342 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2360 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2371 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1430 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1440 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2410 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1444 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2473 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2481 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2521 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1548 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2549 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2559 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1557 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1588 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1604 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2640 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2651 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2660 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2678 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1646 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1654 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1664 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2799 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2819 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1722 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1763 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1779 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1784 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1800 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2912 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1808 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2999 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1878 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1911 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1918 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1921 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3146 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1946 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1955 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3179 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1958 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1961 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1964 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1970 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3212 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 578:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 579:
#line 1986 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3248 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 580:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 581:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 2004 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3309 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3319 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3327 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2032 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2038 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No config_control params are required
    // parsing completed
}
#line 3367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 597:
#line 2057 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3378 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 598:
#line 2062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3387 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3398 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3407 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 607:
#line 2107 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3445 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 610:
#line 2119 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3455 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 611:
#line 2123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3463 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 621:
#line 2140 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 622:
#line 2145 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 623:
#line 2147 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 624:
#line 2153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3501 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 625:
#line 2158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 628:
#line 2167 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 629:
#line 2171 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 636:
#line 2185 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 637:
#line 2187 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 638:
#line 2193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3555 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 639:
#line 2198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 640:
#line 2203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3573 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3577 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -797;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     470,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,    70,    27,    53,    65,   121,
     145,   152,   169,   191,   192,   201,   212,   213,   221,   223,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,    27,    16,
      18,    60,    79,   157,    44,   237,   146,    34,   138,   -62,
     455,    83,    26,  -797,   234,   242,   244,   248,   255,  -797,
    -797,  -797,  -797,  -797,   277,  -797,    43,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,   279,   289,  -797,
    -797,  -797,  -797,  -797,  -797,   302,   303,   309,   311,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
     315,  -797,  -797,  -797,    75,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   319,  -797,
     119,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   321,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   139,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   140,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,   251,   288,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
     335,  -797,  -797,   323,  -797,  -797,  -797,   340,  -797,  -797,
     337,   344,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,   346,   353,  -797,  -797,  -797,
    -797,   350,   345,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,   143,  -797,  -797,  -797,   355,
    -797,  -797,   361,  -797,   364,   365,  -797,  -797,   367,   368,
     370,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   153,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,   159,  -797,  -797,
    -797,  -797,   165,  -797,  -797,  -797,    27,    27,  -797,   216,
     371,   377,   378,   380,   381,  -797,    18,  -797,    26,   382,
     388,   394,   228,   239,   398,   399,   403,   406,   408,   409,
     250,   256,   257,   260,   415,   421,   422,   428,   432,   433,
     434,   435,   436,   437,   438,   280,   439,   441,    60,  -797,
     444,   445,   449,   290,    79,  -797,   450,   451,   453,   454,
     456,   457,   282,   458,   459,   462,   463,   157,  -797,   464,
      44,  -797,   465,   466,   467,   468,   469,   471,   472,   490,
    -797,   237,  -797,   491,   492,   295,   493,   494,   495,   336,
    -797,    34,   497,   339,   342,  -797,   138,   499,   502,   -22,
    -797,   348,   506,   507,   351,   512,   354,   356,   513,   517,
     357,   358,   359,   518,   522,   527,   529,   455,  -797,   530,
      83,  -797,   531,    26,  -797,  -797,  -797,   532,   534,   535,
      27,    27,    27,  -797,   172,   536,   537,   538,  -797,  -797,
     374,   375,   383,   541,   542,   545,  -797,  -797,  -797,  -797,
     546,   547,   549,   550,   551,   393,   552,   554,   555,   556,
     557,  -797,   558,   559,  -797,   564,    94,   167,  -797,  -797,
     400,   423,   424,   579,   425,   426,  -797,   273,   564,   429,
     578,  -797,   430,  -797,   564,   431,   440,   443,   446,   447,
     448,   452,  -797,   473,   474,  -797,   475,   476,   477,  -797,
    -797,   478,  -797,  -797,  -797,   479,    27,  -797,  -797,   480,
     481,  -797,   482,  -797,  -797,    20,   483,  -797,  -797,  -797,
      -8,   484,   485,   486,  -797,   590,  -797,   591,  -797,    27,
      60,    83,  -797,  -797,  -797,  -797,    26,    79,   539,  -797,
    -797,  -797,   442,   442,   592,   593,   594,   595,   597,  -797,
    -797,  -797,   176,   600,   601,   605,    32,    -6,   455,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
     607,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
      97,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   609,   592,  -797,   214,   236,   254,
     263,  -797,   272,  -797,  -797,  -797,  -797,  -797,  -797,   613,
     629,   630,   631,   642,  -797,  -797,   646,   647,   648,   649,
     650,  -797,   274,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   276,  -797,   651,   652,  -797,  -797,   653,   655,  -797,
    -797,   654,   658,  -797,  -797,   656,   660,  -797,  -797,   659,
     661,  -797,  -797,  -797,  -797,  -797,  -797,    58,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,    89,  -797,  -797,   662,   663,
    -797,  -797,   664,   666,  -797,   667,   668,   669,   670,   671,
     672,   284,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,   286,  -797,  -797,  -797,   287,   504,
    -797,   673,   674,  -797,  -797,  -797,  -797,   589,  -797,   126,
    -797,   675,  -797,  -797,  -797,  -797,   676,   539,  -797,   678,
     679,   680,   681,   514,   520,   523,   524,   525,   684,   687,
     528,   533,   540,   543,   544,   442,  -797,  -797,   442,  -797,
     592,   157,  -797,   593,    34,  -797,   594,   138,  -797,   595,
     199,  -797,   597,   176,  -797,   390,   600,  -797,   237,  -797,
     601,   -62,  -797,   605,   548,   553,   560,   561,   562,   563,
      32,  -797,   689,   690,    -6,  -797,  -797,  -797,   692,   693,
      44,  -797,   607,   691,  -797,   175,   609,  -797,  -797,   565,
    -797,   395,   566,   567,   568,  -797,  -797,  -797,  -797,  -797,
     569,   570,  -797,  -797,  -797,  -797,  -797,  -797,   294,  -797,
     296,  -797,   694,  -797,   695,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,   297,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   696,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   697,
     698,  -797,  -797,  -797,  -797,  -797,   700,  -797,   300,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,   571,   573,  -797,
    -797,   574,   318,  -797,   564,  -797,   702,  -797,  -797,  -797,
    -797,  -797,   331,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,   199,  -797,   705,   576,  -797,   390,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,   707,   575,   709,   175,
    -797,  -797,   577,  -797,  -797,   710,  -797,   580,  -797,  -797,
     711,  -797,  -797,   166,  -797,   -91,   711,  -797,  -797,   712,
     715,   716,   338,  -797,  -797,  -797,  -797,  -797,  -797,   717,
     582,   581,   585,   -91,  -797,   583,  -797,  -797,  -797,  -797,
    -797
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   121,     9,   258,    11,
     411,    13,   436,    15,   336,    17,   344,    19,   381,    21,
     223,    23,   526,    25,   601,    27,   591,    29,    47,    41,
       0,     0,     0,     0,     0,   438,     0,   346,   383,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     599,   581,   583,   585,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   587,   589,   110,   136,     0,     0,   457,
     459,   461,   134,   143,   145,     0,     0,     0,     0,   250,
     334,   373,   306,   424,   426,   201,   485,   428,   215,   234,
       0,   511,   524,   103,     0,    72,    74,    75,    76,    77,
      93,    94,    80,    81,   100,    82,    83,    84,    88,    89,
      78,    79,    86,    87,    98,    99,   101,    95,    96,    97,
      85,    90,    91,    92,   102,   123,   125,   129,     0,   120,
       0,   112,   114,   115,   116,   117,   118,   119,   287,   289,
     291,   403,   285,   293,     0,   299,   297,   295,   481,   284,
     262,   263,   264,   275,     0,   260,   267,   279,   280,   281,
     268,   270,   271,   273,   269,   265,   266,   282,   283,   272,
     276,   277,   278,   274,   422,   421,   417,   418,   416,     0,
     413,   415,   419,   420,   479,   467,   469,   473,   471,   477,
     475,   463,   456,   450,   454,   455,     0,   439,   440,   451,
     452,   453,   447,   442,   448,   444,   445,   446,   449,   443,
       0,   363,   186,     0,   367,   365,   370,     0,   359,   360,
       0,   347,   348,   350,   362,   351,   352,   353,   369,   354,
     355,   356,   357,   358,   397,     0,     0,   395,   396,   399,
     400,     0,   384,   385,   387,   388,   389,   390,   391,   392,
     393,   394,   230,   232,   227,     0,   225,   228,   229,     0,
     550,   552,     0,   555,     0,     0,   559,   563,     0,     0,
       0,   568,   575,   577,   579,   548,   546,   547,     0,   528,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   606,     0,   603,   605,
     597,   596,     0,   593,   595,    46,     0,     0,    39,     0,
       0,     0,     0,     0,     0,    57,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    71,
       0,     0,     0,     0,     0,   122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   259,     0,
       0,   412,     0,     0,     0,     0,     0,     0,     0,     0,
     437,     0,   337,     0,     0,     0,     0,     0,     0,     0,
     345,     0,     0,     0,     0,   382,     0,     0,     0,     0,
     224,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   527,     0,
       0,   602,     0,     0,   592,    50,    43,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,     0,   108,   109,
       0,     0,     0,     0,     0,     0,   104,   105,   106,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   510,     0,     0,    73,     0,     0,     0,   133,   113,
       0,     0,     0,     0,     0,     0,   305,     0,     0,     0,
       0,   261,     0,   414,     0,     0,     0,     0,     0,     0,
       0,     0,   441,     0,     0,   361,     0,     0,     0,   372,
     349,     0,   401,   402,   386,     0,     0,   226,   549,     0,
       0,   554,     0,   557,   558,     0,     0,   565,   566,   567,
       0,     0,     0,     0,   529,     0,   604,     0,   594,     0,
       0,     0,   582,   584,   586,   588,     0,     0,     0,   458,
     460,   462,     0,     0,   147,   252,   338,   375,   308,    40,
     425,   427,     0,     0,   430,   217,     0,     0,     0,    51,
     124,   127,   128,   126,   131,   132,   130,   288,   290,   292,
     405,   286,   294,   301,   302,   303,   304,   300,   298,   296,
       0,   423,   480,   468,   470,   474,   472,   478,   476,   464,
     364,   187,   368,   366,   371,   398,   231,   233,   551,   553,
     556,   561,   562,   560,   564,   570,   571,   572,   573,   574,
     569,   576,   578,   580,     0,   147,    44,     0,     0,     0,
       0,   141,     0,   138,   140,   173,   179,   181,   183,     0,
       0,     0,     0,     0,   195,   197,     0,     0,     0,     0,
       0,   172,     0,   153,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   168,   169,   170,   165,   171,   166,
     167,     0,   151,     0,   148,   149,   256,     0,   253,   254,
     342,     0,   339,   340,   379,     0,   376,   377,   312,     0,
     309,   310,   210,   211,   212,   213,   214,     0,   203,   205,
     206,   207,   208,   209,   489,     0,   487,   434,     0,   431,
     432,   221,     0,   218,   219,     0,     0,     0,     0,     0,
       0,     0,   236,   238,   239,   240,   241,   242,   243,   520,
     522,   519,   517,   518,     0,   513,   515,   516,     0,    53,
     409,     0,   406,   407,   465,   483,   484,     0,   610,     0,
     608,     0,    69,   600,   590,   111,     0,     0,   137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,   144,     0,   146,
       0,     0,   251,     0,   346,   335,     0,   383,   374,     0,
       0,   307,     0,     0,   202,   491,     0,   486,   438,   429,
       0,     0,   216,     0,     0,     0,     0,     0,     0,     0,
       0,   235,     0,     0,     0,   512,   525,    55,     0,    54,
       0,   404,     0,     0,   482,     0,     0,   607,   598,     0,
     139,     0,     0,     0,     0,   185,   188,   189,   190,   191,
       0,     0,   199,   200,   192,   193,   194,   154,     0,   150,
       0,   255,     0,   341,     0,   378,   333,   330,   319,   320,
     322,   316,   317,   318,   328,   329,   327,     0,   314,   321,
     331,   332,   323,   324,   325,   326,   311,   204,   507,     0,
     505,   506,   498,   499,   503,   504,   500,   501,   502,     0,
     492,   493,   495,   496,   497,   488,     0,   433,     0,   220,
     244,   245,   246,   247,   248,   249,   237,     0,     0,   514,
      52,     0,     0,   408,     0,   624,     0,   622,   620,   614,
     618,   619,     0,   612,   616,   617,   615,   609,   142,   175,
     176,   177,   178,   174,   180,   182,   184,   196,   198,   152,
     257,   343,   380,     0,   313,     0,     0,   490,     0,   435,
     222,   521,   523,    56,   410,   466,     0,     0,     0,     0,
     611,   315,     0,   509,   494,     0,   621,     0,   613,   508,
       0,   623,   628,     0,   626,     0,     0,   625,   636,     0,
       0,     0,     0,   630,   632,   633,   634,   635,   627,     0,
       0,     0,     0,     0,   629,     0,   638,   639,   640,   631,
     637
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,   -37,  -797,   104,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -497,  -797,  -797,
    -797,   -70,  -797,  -797,  -797,   343,  -797,  -797,  -797,  -797,
      86,   326,   -47,   -18,   -11,  -797,  -797,     8,  -797,  -797,
     177,   328,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   -64,  -797,
    -797,  -797,  -797,  -797,  -797,   108,  -797,   -45,  -797,  -570,
     -29,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   -48,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   -55,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   -54,
    -797,  -797,  -797,   -56,   349,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,   -57,  -797,  -797,  -797,  -797,  -797,  -797,  -796,
    -797,  -797,  -797,   -35,  -797,  -797,  -797,   -20,   389,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -795,  -797,   -68,
    -797,   -15,  -797,  -785,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,   -33,  -797,  -797,  -174,   -65,  -797,  -797,  -797,  -797,
    -797,   -12,  -797,  -797,  -797,     3,  -797,   385,  -797,   -66,
    -797,  -797,  -797,  -797,  -797,   -60,  -797,  -797,  -797,  -797,
    -797,   -17,  -797,  -797,  -797,   -13,  -797,  -797,  -797,     6,
    -797,   396,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,   -28,  -797,  -797,  -797,   -19,   427,  -797,
    -797,   -58,  -797,   -30,  -797,   -40,  -797,  -797,  -797,     4,
    -797,  -797,  -797,    10,  -797,   418,   -10,  -797,     1,  -797,
       2,  -797,   220,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -779,  -797,  -797,  -797,  -797,  -797,    15,  -797,  -797,  -797,
    -142,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,    -2,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,   245,   387,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,
    -797,  -797,  -797,  -797,  -797,  -797,  -797,  -797,  -335,   384,
    -797,  -797,  -797,  -797,  -797,  -797,   275,   391,  -797,  -797,
    -797,    -7,  -797,  -797,  -144,  -797,  -797,  -797,  -797,  -797,
    -797,  -158,  -797,  -797,  -173,  -797,  -797,  -797,  -797,  -797
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     590,    87,    88,    41,    68,    84,    85,   600,   769,   848,
     849,   341,    43,    70,    96,    97,    98,   350,    45,    71,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   360,
     170,   171,    47,    72,   172,   390,   173,   391,   603,   174,
     392,   606,   175,   143,   367,   144,   361,   662,   663,   664,
     786,   145,   368,   146,   369,   703,   704,   705,   808,   682,
     683,   684,   789,   963,   685,   790,   686,   791,   687,   792,
     688,   689,   424,   690,   691,   692,   693,   694,   695,   696,
     697,   798,   698,   799,   699,   700,   147,   380,   727,   728,
     729,   730,   731,   732,   733,   148,   383,   742,   743,   744,
     831,    61,    79,   295,   296,   297,   437,   298,   438,   149,
     384,   751,   752,   753,   754,   755,   756,   757,   758,   150,
     374,   707,   708,   709,   811,    49,    73,   194,   195,   196,
     400,   197,   396,   198,   397,   199,   398,   200,   401,   201,
     405,   202,   404,   203,   403,   617,   204,   151,   377,   719,
     720,   721,   820,   897,   898,   152,   375,    55,    76,   711,
     712,   713,   814,    57,    77,   260,   261,   262,   263,   264,
     265,   266,   423,   267,   427,   268,   426,   269,   270,   428,
     271,   153,   376,   715,   716,   717,   817,    59,    78,   281,
     282,   283,   284,   285,   432,   286,   287,   288,   289,   206,
     399,   771,   772,   773,   850,    51,    74,   219,   220,   221,
     409,   154,   378,   155,   379,   156,   382,   738,   739,   740,
     828,    53,    75,   236,   237,   238,   157,   364,   158,   365,
     159,   366,   242,   419,   776,   853,   243,   413,   244,   414,
     245,   416,   246,   415,   247,   418,   248,   417,   249,   412,
     213,   406,   777,   160,   381,   735,   736,   825,   919,   920,
     921,   922,   923,   975,   924,   161,   162,   386,   764,   765,
     766,   842,   767,   843,   163,   387,    63,    80,   318,   319,
     320,   321,   442,   322,   443,   323,   324,   445,   325,   326,
     327,   448,   643,   328,   449,   329,   330,   331,   332,   453,
     650,   333,   454,   334,   455,   335,   456,    99,   352,   100,
     353,   101,   354,   164,   358,   359,    67,    82,   342,   343,
     344,   462,   102,   351,    65,    81,   337,   338,   339,   459,
     779,   780,   855,   952,   953,   954,   955,   988,   956,   986,
    1003,  1004,  1005,  1012,  1013,  1014,  1019,  1015,  1016,  1017
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      95,   133,   169,   189,   215,   232,   216,   258,   277,   294,
     315,   250,   279,   701,   176,   207,   222,   234,   280,   272,
     290,   618,   316,   474,   892,   893,   190,   622,    89,   259,
     278,    83,    31,   209,    32,   896,    33,   641,   340,   292,
     293,   905,   177,   208,   223,   235,   356,   273,   291,  1008,
     317,   357,  1009,  1010,  1011,   191,   205,   218,   233,   217,
      42,   823,   192,   210,   824,   239,   251,   103,   123,   124,
      30,   104,    44,   105,   211,   212,   240,   241,   388,   292,
     293,   193,   106,   389,   107,   108,   109,   110,   111,   112,
     113,   114,   826,   165,   166,   827,   252,   167,   253,   254,
     168,    94,   255,   256,   257,   121,   759,   760,   123,   124,
     601,   602,   115,   116,   117,   118,   119,   214,   123,   124,
     120,   121,   394,   645,   646,   647,   648,   395,    46,   856,
     186,   122,   857,   187,   123,   124,   745,   746,   747,   748,
     749,   750,   407,   410,   125,   126,   439,   408,   411,   642,
     127,   440,    48,   123,   124,    90,   457,    94,   649,    50,
     128,   458,   460,   129,    91,    92,    93,   461,   463,  1006,
     130,   131,  1007,   464,   132,   463,    52,   892,   893,    86,
     575,    94,   108,   109,   110,   111,   604,   605,   896,    94,
      34,    35,    36,    37,   905,   231,   774,    94,    54,    56,
     252,   274,   253,   254,   275,   276,   120,    94,    58,   115,
     116,   117,   123,   124,   178,   179,   180,   388,   121,    60,
      62,   336,   782,    94,   108,   109,   110,   111,    64,   181,
      66,   123,   124,   182,   183,   184,   185,   252,   878,   460,
     345,   659,    94,   186,   783,   346,   187,   127,   347,   123,
     124,   115,   116,   117,   188,   119,   348,   463,   349,   420,
     121,   252,   784,   109,   110,   111,   394,   722,   723,   724,
     725,   785,   726,   123,   124,   787,   183,   805,   185,   805,
     788,   355,   806,   362,   807,   186,    95,   840,   187,   844,
     457,   421,   841,   363,   845,   846,   188,   805,   121,   407,
     973,    94,   969,   439,   970,   974,   370,   371,   980,   465,
     466,   123,   124,   372,   945,   373,   946,   947,   133,   385,
      94,   410,   224,   393,   169,   402,   984,   425,   225,   226,
     227,   228,   229,   230,   989,   231,   176,   189,    94,   990,
     215,  1023,   216,   422,   429,   430,  1024,   431,   436,   207,
     433,   232,   222,   613,   614,   615,   616,   434,   435,   441,
     190,   258,    94,   234,   177,   444,   277,   209,   446,   447,
     279,   450,   451,   272,   452,   468,   280,   208,   290,   467,
     223,   469,   470,   259,   471,   472,   475,   315,   278,   191,
     205,   235,   476,   218,   478,   217,   192,   210,   477,   316,
      94,   273,   480,   481,   233,   479,   291,   482,   211,   212,
     483,   239,   484,   485,   486,   193,   109,   110,   111,   490,
     487,   488,   240,   241,   489,   491,   492,   317,   959,   960,
     961,   962,   493,   572,   573,   574,   494,   495,   496,   497,
     498,   499,   500,   502,   501,   503,   516,   985,   505,   506,
     120,   121,   252,   507,   510,   511,   508,   512,   513,   535,
     514,   515,   517,   518,   123,   124,   519,   520,   522,   524,
     525,   526,   527,   528,   665,   529,   530,   908,   909,   666,
     667,   668,   669,   670,   671,   672,   673,   674,   675,   676,
     677,   678,   679,   680,   531,   533,   534,   536,   537,   538,
     133,   541,   539,   545,   252,   542,   546,   169,   543,   637,
     549,   550,   681,   681,   548,   551,   552,   555,   553,   176,
     554,   556,   560,   557,   558,   559,   561,   761,   315,   123,
     124,   562,   656,   563,   565,   567,   569,   579,   580,   762,
     316,   570,   571,   576,   577,   578,   581,   177,   582,   583,
     584,   585,   586,    94,   587,   588,   591,   592,    32,   593,
     594,   595,   661,   607,   596,   597,   598,   763,   317,   599,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   610,   620,   608,   609,   611,   612,
     313,   314,   619,   621,   623,   654,   655,   854,   589,   702,
     706,   710,   714,   624,   718,    94,   625,   734,   737,   626,
     627,   628,   741,   644,   770,   629,   778,   793,    94,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   794,   795,   796,   630,   631,   632,   633,
     634,   635,   636,   638,   639,   640,   797,   651,   652,   653,
     800,   801,   802,   803,   804,   810,   657,   809,   813,   812,
     815,   816,   818,   819,   822,   821,   830,   847,   829,   833,
     832,   834,   835,   836,   837,   838,   839,   852,   865,   851,
     859,   858,   861,   862,   863,   864,   866,   867,   870,   869,
     868,   871,   872,   937,   938,   944,   941,   873,   940,   473,
     976,   978,   971,   972,   874,   977,   987,   875,   979,   992,
     876,   995,   930,   997,   504,  1000,  1020,   931,  1002,  1021,
    1022,  1025,   509,   860,   932,   933,   934,   935,   958,   964,
     965,   966,   967,   968,   981,   681,   982,   983,   681,   996,
     999,   189,   993,  1001,   258,  1027,  1030,   277,  1026,  1028,
     886,   279,   894,   207,   660,   910,   272,   280,   232,   290,
     912,   294,   900,   781,   190,   879,   259,   914,   907,   278,
     234,   209,   891,   887,   761,   928,   877,   911,   881,   929,
     215,   208,   216,   936,   273,   948,   762,   291,   547,   906,
     901,   880,   222,   191,   205,   915,   521,   950,   235,   991,
     192,   210,   888,   899,   883,   895,   885,   949,   913,   889,
     902,   233,   211,   212,   763,   916,   540,   882,   239,   193,
     223,   903,   904,   884,   943,   951,   917,   918,   890,   240,
     241,   942,   544,   218,   927,   217,   994,   523,   926,   532,
     775,   925,   939,   768,   564,   998,   658,   568,  1018,   957,
    1029,   566,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   886,     0,   894,     0,     0,   910,     0,
       0,     0,     0,   912,     0,   900,     0,     0,     0,   948,
     914,     0,     0,     0,     0,   891,   887,     0,     0,     0,
     911,   950,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   949,     0,   901,     0,     0,     0,     0,   915,     0,
       0,     0,     0,     0,     0,   888,   899,     0,   895,   951,
       0,   913,   889,   902,     0,     0,     0,     0,   916,     0,
       0,     0,     0,     0,   903,   904,     0,     0,     0,   917,
     918,   890
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    76,    78,   583,    72,    73,    74,    75,    78,    77,
      78,   518,    80,   358,   820,   820,    73,   524,    10,    77,
      78,    68,     5,    73,     7,   820,     9,    17,    12,   101,
     102,   820,    72,    73,    74,    75,     3,    77,    78,   140,
      80,     8,   143,   144,   145,    73,    73,    74,    75,    74,
       7,     3,    73,    73,     6,    75,    32,     7,    74,    75,
       0,    11,     7,    13,    73,    73,    75,    75,     3,   101,
     102,    73,    22,     8,    24,    25,    26,    27,    28,    29,
      30,    31,     3,    14,    15,     6,    62,    18,    64,    65,
      21,   163,    68,    69,    70,    61,   112,   113,    74,    75,
      16,    17,    52,    53,    54,    55,    56,    73,    74,    75,
      60,    61,     3,   131,   132,   133,   134,     8,     7,     3,
      86,    71,     6,    89,    74,    75,   104,   105,   106,   107,
     108,   109,     3,     3,    84,    85,     3,     8,     8,   129,
      90,     8,     7,    74,    75,   137,     3,   163,   166,     7,
     100,     8,     3,   103,   146,   147,   148,     8,     3,     3,
     110,   111,     6,     8,   114,     3,     7,   973,   973,   163,
       8,   163,    25,    26,    27,    28,    19,    20,   973,   163,
     163,   164,   165,   166,   973,    98,    99,   163,     7,     7,
      62,    63,    64,    65,    66,    67,    60,   163,     7,    52,
      53,    54,    74,    75,    57,    58,    59,     3,    61,     7,
       7,   138,     8,   163,    25,    26,    27,    28,     7,    72,
       7,    74,    75,    76,    77,    78,    79,    62,   808,     3,
       6,   576,   163,    86,     8,     3,    89,    90,     4,    74,
      75,    52,    53,    54,    97,    56,     8,     3,     3,     8,
      61,    62,     8,    26,    27,    28,     3,    91,    92,    93,
      94,     8,    96,    74,    75,     3,    77,     3,    79,     3,
       8,     4,     8,     4,     8,    86,   356,     3,    89,     3,
       3,     3,     8,     4,     8,     8,    97,     3,    61,     3,
       3,   163,     8,     3,     8,     8,     4,     4,     8,   346,
     347,    74,    75,     4,   139,     4,   141,   142,   388,     4,
     163,     3,    85,     4,   394,     4,     8,     4,    91,    92,
      93,    94,    95,    96,     3,    98,   394,   407,   163,     8,
     410,     3,   410,     8,     4,     8,     8,     3,     3,   407,
       4,   421,   410,    80,    81,    82,    83,     4,     8,     4,
     407,   431,   163,   421,   394,     4,   436,   407,     4,     4,
     436,     4,     4,   431,     4,     4,   436,   407,   436,   163,
     410,     4,     4,   431,     4,     4,     4,   457,   436,   407,
     407,   421,     4,   410,   166,   410,   407,   407,     4,   457,
     163,   431,     4,     4,   421,   166,   436,     4,   407,   407,
       4,   421,     4,     4,   164,   407,    26,    27,    28,     4,
     164,   164,   421,   421,   164,     4,     4,   457,    33,    34,
      35,    36,     4,   470,   471,   472,     4,     4,     4,     4,
       4,     4,     4,     4,   164,     4,   164,   944,     4,     4,
      60,    61,    62,     4,     4,     4,   166,     4,     4,   164,
       4,     4,     4,     4,    74,    75,     4,     4,     4,     4,
       4,     4,     4,     4,    32,     4,     4,    87,    88,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,     4,     4,     4,     4,     4,     4,
     570,     4,   166,     4,    62,   166,     4,   577,   166,   546,
       4,     4,   582,   583,   166,   164,     4,     4,   164,   577,
     164,     4,     4,   166,   166,   166,     4,   597,   598,    74,
      75,     4,   569,     4,     4,     4,     4,   163,   163,   597,
     598,     7,     7,     7,     7,     7,   163,   577,     7,     7,
       5,     5,     5,   163,     5,     5,   163,     5,     7,     5,
       5,     5,    23,   163,     7,     7,     7,   597,   598,     5,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,     5,     7,   163,   163,   163,   163,
     135,   136,   163,   163,   163,     5,     5,     8,   494,     7,
       7,     7,     7,   163,     7,   163,   163,     7,     7,   163,
     163,   163,     7,   130,     7,   163,     7,     4,   163,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,     4,     4,     4,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,     4,   163,   163,   163,
       4,     4,     4,     4,     4,     3,   570,     6,     3,     6,
       6,     3,     6,     3,     3,     6,     3,   163,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     3,   164,     6,
       4,     6,     4,     4,     4,     4,   166,   164,     4,   164,
     166,     4,   164,     4,     4,     4,     3,   164,     6,   356,
       4,     3,     8,     8,   164,     8,     4,   164,     8,     4,
     166,     4,   164,     4,   388,     5,     4,   164,     7,     4,
       4,     4,   394,   787,   164,   164,   164,   164,   163,   163,
     163,   163,   163,   163,   163,   805,   163,   163,   808,   164,
     163,   811,   166,   163,   814,   164,   163,   817,   166,   164,
     820,   817,   820,   811,   577,   825,   814,   817,   828,   817,
     825,   831,   820,   655,   811,   810,   814,   825,   823,   817,
     828,   811,   820,   820,   844,   831,   805,   825,   813,   833,
     850,   811,   850,   840,   814,   855,   844,   817,   439,   822,
     820,   811,   850,   811,   811,   825,   407,   855,   828,   973,
     811,   811,   820,   820,   816,   820,   819,   855,   825,   820,
     820,   828,   811,   811,   844,   825,   431,   814,   828,   811,
     850,   820,   820,   817,   852,   855,   825,   825,   820,   828,
     828,   850,   436,   850,   830,   850,   978,   410,   828,   421,
     620,   826,   844,   598,   457,   989,   571,   463,  1006,   856,
    1023,   460,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   973,    -1,   973,    -1,    -1,   978,    -1,
      -1,    -1,    -1,   978,    -1,   973,    -1,    -1,    -1,   989,
     978,    -1,    -1,    -1,    -1,   973,   973,    -1,    -1,    -1,
     978,   989,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   989,    -1,   973,    -1,    -1,    -1,    -1,   978,    -1,
      -1,    -1,    -1,    -1,    -1,   973,   973,    -1,   973,   989,
      -1,   978,   973,   973,    -1,    -1,    -1,    -1,   978,    -1,
      -1,    -1,    -1,    -1,   973,   973,    -1,    -1,    -1,   978,
     978,   973
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
       0,     5,     7,     9,   163,   164,   165,   166,   183,   184,
     185,   190,     7,   199,     7,   205,     7,   219,     7,   312,
       7,   392,     7,   408,     7,   344,     7,   350,     7,   374,
       7,   288,     7,   463,     7,   511,     7,   503,   191,   186,
     200,   206,   220,   313,   393,   409,   345,   351,   375,   289,
     464,   512,   504,   183,   192,   193,   163,   188,   189,    10,
     137,   146,   147,   148,   163,   198,   201,   202,   203,   494,
     496,   498,   509,     7,    11,    13,    22,    24,    25,    26,
      27,    28,    29,    30,    31,    52,    53,    54,    55,    56,
      60,    61,    71,    74,    75,    84,    85,    90,   100,   103,
     110,   111,   114,   198,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   230,   232,   238,   240,   273,   282,   296,
     306,   334,   342,   368,   398,   400,   402,   413,   415,   417,
     440,   452,   453,   461,   500,    14,    15,    18,    21,   198,
     217,   218,   221,   223,   226,   229,   398,   400,    57,    58,
      59,    72,    76,    77,    78,    79,    86,    89,    97,   198,
     209,   210,   211,   214,   314,   315,   316,   318,   320,   322,
     324,   326,   328,   330,   333,   368,   386,   398,   400,   402,
     413,   415,   417,   437,    73,   198,   326,   328,   368,   394,
     395,   396,   398,   400,    85,    91,    92,    93,    94,    95,
      96,    98,   198,   368,   398,   400,   410,   411,   412,   413,
     415,   417,   419,   423,   425,   427,   429,   431,   433,   435,
     342,    32,    62,    64,    65,    68,    69,    70,   198,   258,
     352,   353,   354,   355,   356,   357,   358,   360,   362,   364,
     365,   367,   398,   400,    63,    66,    67,   198,   258,   356,
     362,   376,   377,   378,   379,   380,   382,   383,   384,   385,
     398,   400,   101,   102,   198,   290,   291,   292,   294,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   135,   136,   198,   398,   400,   465,   466,
     467,   468,   470,   472,   473,   475,   476,   477,   480,   482,
     483,   484,   485,   488,   490,   492,   138,   513,   514,   515,
      12,   198,   505,   506,   507,     6,     3,     4,     8,     3,
     204,   510,   495,   497,   499,     4,     3,     8,   501,   502,
     216,   233,     4,     4,   414,   416,   418,   231,   239,   241,
       4,     4,     4,     4,   307,   343,   369,   335,   399,   401,
     274,   441,   403,   283,   297,     4,   454,   462,     3,     8,
     222,   224,   227,     4,     3,     8,   319,   321,   323,   387,
     317,   325,     4,   331,   329,   327,   438,     3,     8,   397,
       3,     8,   436,   424,   426,   430,   428,   434,   432,   420,
       8,     3,     8,   359,   259,     4,   363,   361,   366,     4,
       8,     3,   381,     4,     4,     8,     3,   293,   295,     3,
       8,     4,   469,   471,     4,   474,     4,     4,   478,   481,
       4,     4,     4,   486,   489,   491,   493,     3,     8,   516,
       3,     8,   508,     3,     8,   183,   183,   163,     4,     4,
       4,     4,     4,   202,   505,     4,     4,     4,   166,   166,
       4,     4,     4,     4,     4,     4,   164,   164,   164,   164,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   164,     4,     4,   208,     4,     4,     4,   166,   218,
       4,     4,     4,     4,     4,     4,   164,     4,     4,     4,
       4,   315,     4,   395,     4,     4,     4,     4,     4,     4,
       4,     4,   412,     4,     4,   164,     4,     4,     4,   166,
     354,     4,   166,   166,   378,     4,     4,   291,   166,     4,
       4,   164,     4,   164,   164,     4,     4,   166,   166,   166,
       4,     4,     4,     4,   466,     4,   514,     4,   506,     4,
       7,     7,   183,   183,   183,     8,     7,     7,     7,   163,
     163,   163,     7,     7,     5,     5,     5,     5,     5,   185,
     187,   163,     5,     5,     5,     5,     7,     7,     7,     5,
     194,    16,    17,   225,    19,    20,   228,   163,   163,   163,
       5,   163,   163,    80,    81,    82,    83,   332,   194,   163,
       7,   163,   194,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   183,   163,   163,
     163,    17,   129,   479,   130,   131,   132,   133,   134,   166,
     487,   163,   163,   163,     5,     5,   183,   207,   513,   505,
     217,    23,   234,   235,   236,    32,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   198,   246,   247,   248,   251,   253,   255,   257,   258,
     260,   261,   262,   263,   264,   265,   266,   267,   269,   271,
     272,   246,     7,   242,   243,   244,     7,   308,   309,   310,
       7,   346,   347,   348,     7,   370,   371,   372,     7,   336,
     337,   338,    91,    92,    93,    94,    96,   275,   276,   277,
     278,   279,   280,   281,     7,   442,   443,     7,   404,   405,
     406,     7,   284,   285,   286,   104,   105,   106,   107,   108,
     109,   298,   299,   300,   301,   302,   303,   304,   305,   112,
     113,   198,   398,   400,   455,   456,   457,   459,   465,   195,
       7,   388,   389,   390,    99,   419,   421,   439,     7,   517,
     518,   242,     8,     8,     8,     8,   237,     3,     8,   249,
     252,   254,   256,     4,     4,     4,     4,     4,   268,   270,
       4,     4,     4,     4,     4,     3,     8,     8,   245,     6,
       3,   311,     6,     3,   349,     6,     3,   373,     6,     3,
     339,     6,     3,     3,     6,   444,     3,     6,   407,     6,
       3,   287,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   458,   460,     3,     8,     8,   163,   196,   197,
     391,     6,     3,   422,     8,   519,     3,     6,     6,     4,
     235,     4,     4,     4,     4,   164,   166,   164,   166,   164,
       4,     4,   164,   164,   164,   164,   166,   247,   246,   244,
     314,   310,   352,   348,   376,   372,   198,   209,   210,   211,
     214,   258,   306,   324,   326,   328,   330,   340,   341,   368,
     398,   400,   413,   415,   417,   437,   338,   276,    87,    88,
     198,   258,   342,   368,   398,   400,   413,   415,   417,   445,
     446,   447,   448,   449,   451,   443,   410,   406,   290,   286,
     164,   164,   164,   164,   164,   164,   299,     4,     4,   456,
       6,     3,   394,   390,     4,   139,   141,   142,   198,   258,
     398,   400,   520,   521,   522,   523,   525,   518,   163,    33,
      34,    35,    36,   250,   163,   163,   163,   163,   163,     8,
       8,     8,     8,     3,     8,   450,     4,     8,     3,     8,
       8,   163,   163,   163,     8,   194,   526,     4,   524,     3,
       8,   341,     4,   166,   447,     4,   164,     4,   521,   163,
       5,   163,     7,   527,   528,   529,     3,     6,   140,   143,
     144,   145,   530,   531,   532,   534,   535,   536,   528,   533,
       4,     4,     4,     3,     8,     4,   166,   164,   164,   531,
     163
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   167,   169,   168,   170,   168,   171,   168,   172,   168,
     173,   168,   174,   168,   175,   168,   176,   168,   177,   168,
     178,   168,   179,   168,   180,   168,   181,   168,   182,   168,
     183,   183,   183,   183,   183,   183,   183,   184,   186,   185,
     187,   188,   188,   189,   189,   191,   190,   192,   192,   193,
     193,   195,   194,   196,   196,   197,   197,   198,   200,   199,
     201,   201,   202,   202,   202,   202,   202,   202,   204,   203,
     206,   205,   207,   207,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   209,   210,   211,   212,   213,   214,
     216,   215,   217,   217,   218,   218,   218,   218,   218,   218,
     218,   220,   219,   222,   221,   224,   223,   225,   225,   227,
     226,   228,   228,   229,   231,   230,   233,   232,   234,   234,
     235,   237,   236,   239,   238,   241,   240,   242,   242,   243,
     243,   245,   244,   246,   246,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   249,   248,   250,   250,   250,   250,   252,
     251,   254,   253,   256,   255,   257,   259,   258,   260,   261,
     262,   263,   264,   265,   266,   268,   267,   270,   269,   271,
     272,   274,   273,   275,   275,   276,   276,   276,   276,   276,
     277,   278,   279,   280,   281,   283,   282,   284,   284,   285,
     285,   287,   286,   289,   288,   290,   290,   290,   291,   291,
     293,   292,   295,   294,   297,   296,   298,   298,   299,   299,
     299,   299,   299,   299,   300,   301,   302,   303,   304,   305,
     307,   306,   308,   308,   309,   309,   311,   310,   313,   312,
     314,   314,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   315,   317,   316,   319,   318,   321,
     320,   323,   322,   325,   324,   327,   326,   329,   328,   331,
     330,   332,   332,   332,   332,   333,   335,   334,   336,   336,
     337,   337,   339,   338,   340,   340,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   343,   342,   345,   344,   346,   346,
     347,   347,   349,   348,   351,   350,   352,   352,   353,   353,
     354,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     355,   356,   357,   359,   358,   361,   360,   363,   362,   364,
     366,   365,   367,   369,   368,   370,   370,   371,   371,   373,
     372,   375,   374,   376,   376,   377,   377,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   379,   381,   380,   382,
     383,   384,   385,   387,   386,   388,   388,   389,   389,   391,
     390,   393,   392,   394,   394,   395,   395,   395,   395,   395,
     395,   395,   397,   396,   399,   398,   401,   400,   403,   402,
     404,   404,   405,   405,   407,   406,   409,   408,   410,   410,
     411,   411,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   414,   413,   416,
     415,   418,   417,   420,   419,   422,   421,   424,   423,   426,
     425,   428,   427,   430,   429,   432,   431,   434,   433,   436,
     435,   438,   437,   439,   439,   441,   440,   442,   442,   444,
     443,   445,   445,   446,   446,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   448,   450,   449,   451,
     452,   454,   453,   455,   455,   456,   456,   456,   456,   456,
     458,   457,   460,   459,   462,   461,   464,   463,   465,   465,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   467,
     469,   468,   471,   470,   472,   474,   473,   475,   476,   478,
     477,   479,   479,   481,   480,   482,   483,   484,   486,   485,
     487,   487,   487,   487,   487,   489,   488,   491,   490,   493,
     492,   495,   494,   497,   496,   499,   498,   501,   500,   502,
     500,   504,   503,   505,   505,   506,   506,   508,   507,   510,
     509,   512,   511,   513,   513,   514,   516,   515,   517,   517,
     519,   518,   520,   520,   521,   521,   521,   521,   521,   521,
     521,   522,   524,   523,   526,   525,   527,   527,   529,   528,
     530,   530,   531,   531,   531,   531,   533,   532,   534,   535,
     536
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     1,     1,     0,
       4,     1,     1,     3,     0,     6,     0,     6,     1,     3,
       1,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     0,     6,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
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
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"echo-client-id\"",
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
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
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
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@21",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@22", "interfaces_list", "$@23", "dhcp_socket_type", "$@24",
  "socket_type", "outbound_interface", "$@25", "outbound_interface_value",
  "re_detect", "lease_database", "$@26", "sanity_checks", "$@27",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@28",
  "hosts_database", "$@29", "hosts_databases", "$@30", "database_list",
  "not_empty_database_list", "database", "$@31", "database_map_params",
  "database_map_param", "database_type", "$@32", "db_type", "user", "$@33",
  "password", "$@34", "host", "$@35", "port", "name", "$@36", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@37", "keyspace",
  "$@38", "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@39",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@40", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@41",
  "sub_hooks_library", "$@42", "hooks_params", "hooks_param", "library",
  "$@43", "parameters", "$@44", "expired_leases_processing", "$@45",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@46",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@47",
  "sub_subnet4", "$@48", "subnet4_params", "subnet4_param", "subnet",
  "$@49", "subnet_4o6_interface", "$@50", "subnet_4o6_interface_id",
  "$@51", "subnet_4o6_subnet", "$@52", "interface", "$@53", "client_class",
  "$@54", "require_client_classes", "$@55", "reservation_mode", "$@56",
  "hr_mode", "id", "shared_networks", "$@57", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@58",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@59", "sub_option_def_list", "$@60", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@61",
  "sub_option_def", "$@62", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@63",
  "option_def_record_types", "$@64", "space", "$@65", "option_def_space",
  "option_def_encapsulate", "$@66", "option_def_array", "option_data_list",
  "$@67", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@68", "sub_option_data", "$@69",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@70",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@71", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@72", "sub_pool4", "$@73",
  "pool_params", "pool_param", "pool_entry", "$@74", "user_context",
  "$@75", "comment", "$@76", "reservations", "$@77", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@78", "sub_reservation",
  "$@79", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@80", "server_hostname", "$@81",
  "boot_file_name", "$@82", "ip_address", "$@83", "ip_addresses", "$@84",
  "duid", "$@85", "hw_address", "$@86", "client_id_value", "$@87",
  "circuit_id_value", "$@88", "flex_id_value", "$@89", "hostname", "$@90",
  "reservation_client_classes", "$@91", "relay", "$@92", "relay_map",
  "client_classes", "$@93", "client_classes_list", "client_class_entry",
  "$@94", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@95",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@96",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@97", "control_socket_name", "$@98", "dhcp_ddns", "$@99",
  "sub_dhcp_ddns", "$@100", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@101", "server_ip", "$@102",
  "server_port", "sender_ip", "$@103", "sender_port", "max_queue_size",
  "ncr_protocol", "$@104", "ncr_protocol_value", "ncr_format", "$@105",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@106", "replace_client_name_value",
  "generated_prefix", "$@107", "hostname_char_set", "$@108",
  "hostname_char_replacement", "$@109", "dhcp6_json_object", "$@110",
  "dhcpddns_json_object", "$@111", "control_agent_json_object", "$@112",
  "config_control", "$@113", "$@114", "sub_config_control", "$@115",
  "config_control_params", "config_control_param", "config_databases",
  "$@116", "logging_object", "$@117", "sub_logging", "$@118",
  "logging_params", "logging_param", "loggers", "$@119", "loggers_entries",
  "logger_entry", "$@120", "logger_params", "logger_param", "debuglevel",
  "severity", "$@121", "output_options_list", "$@122",
  "output_options_list_content", "output_entry", "$@123",
  "output_params_list", "output_params", "output", "$@124", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   251,   251,   251,   252,   252,   253,   253,   254,   254,
     255,   255,   256,   256,   257,   257,   258,   258,   259,   259,
     260,   260,   261,   261,   262,   262,   263,   263,   264,   264,
     272,   273,   274,   275,   276,   277,   278,   281,   286,   286,
     297,   300,   301,   304,   308,   315,   315,   322,   323,   326,
     330,   337,   337,   344,   345,   348,   352,   363,   373,   373,
     389,   390,   394,   395,   396,   397,   398,   399,   402,   402,
     417,   417,   426,   427,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   464,   469,   474,   479,   484,   489,
     495,   495,   506,   507,   510,   511,   512,   513,   514,   515,
     516,   519,   519,   528,   528,   538,   538,   545,   546,   549,
     549,   556,   558,   562,   568,   568,   580,   580,   590,   591,
     593,   595,   595,   613,   613,   625,   625,   635,   636,   639,
     640,   643,   643,   653,   654,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     672,   673,   674,   677,   677,   684,   685,   686,   687,   690,
     690,   698,   698,   706,   706,   714,   719,   719,   727,   732,
     737,   742,   747,   752,   757,   762,   762,   770,   770,   778,
     783,   788,   788,   798,   799,   802,   803,   804,   805,   806,
     809,   814,   819,   824,   829,   834,   834,   844,   845,   848,
     849,   852,   852,   862,   862,   872,   873,   874,   877,   878,
     881,   881,   889,   889,   897,   897,   908,   909,   912,   913,
     914,   915,   916,   917,   920,   925,   930,   935,   940,   945,
     953,   953,   966,   967,   970,   971,   978,   978,  1004,  1004,
    1015,  1016,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,  1045,  1045,  1053,  1053,  1061,
    1061,  1069,  1069,  1077,  1077,  1085,  1085,  1093,  1093,  1103,
    1103,  1110,  1111,  1112,  1113,  1116,  1123,  1123,  1134,  1135,
    1139,  1140,  1143,  1143,  1151,  1152,  1155,  1156,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,
    1169,  1170,  1171,  1172,  1179,  1179,  1192,  1192,  1201,  1202,
    1205,  1206,  1211,  1211,  1226,  1226,  1240,  1241,  1244,  1245,
    1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,  1257,
    1260,  1262,  1267,  1269,  1269,  1277,  1277,  1285,  1285,  1293,
    1295,  1295,  1303,  1312,  1312,  1324,  1325,  1330,  1331,  1336,
    1336,  1348,  1348,  1360,  1361,  1366,  1367,  1372,  1373,  1374,
    1375,  1376,  1377,  1378,  1379,  1380,  1383,  1385,  1385,  1393,
    1395,  1397,  1402,  1410,  1410,  1422,  1423,  1426,  1427,  1430,
    1430,  1440,  1440,  1450,  1451,  1454,  1455,  1456,  1457,  1458,
    1459,  1460,  1463,  1463,  1471,  1471,  1496,  1496,  1526,  1526,
    1536,  1537,  1540,  1541,  1544,  1544,  1553,  1553,  1562,  1563,
    1566,  1567,  1571,  1572,  1573,  1574,  1575,  1576,  1577,  1578,
    1579,  1580,  1581,  1582,  1583,  1584,  1585,  1588,  1588,  1596,
    1596,  1604,  1604,  1612,  1612,  1620,  1620,  1630,  1630,  1638,
    1638,  1646,  1646,  1654,  1654,  1662,  1662,  1670,  1670,  1678,
    1678,  1691,  1691,  1701,  1702,  1708,  1708,  1718,  1719,  1722,
    1722,  1732,  1733,  1736,  1737,  1740,  1741,  1742,  1743,  1744,
    1745,  1746,  1747,  1748,  1749,  1750,  1753,  1755,  1755,  1763,
    1772,  1779,  1779,  1789,  1790,  1793,  1794,  1795,  1796,  1797,
    1800,  1800,  1808,  1808,  1818,  1818,  1830,  1830,  1840,  1841,
    1844,  1845,  1846,  1847,  1848,  1849,  1850,  1851,  1852,  1853,
    1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,  1865,
    1870,  1870,  1878,  1878,  1886,  1891,  1891,  1899,  1904,  1909,
    1909,  1917,  1918,  1921,  1921,  1929,  1934,  1939,  1944,  1944,
    1952,  1955,  1958,  1961,  1964,  1970,  1970,  1978,  1978,  1986,
    1986,  1997,  1997,  2004,  2004,  2011,  2011,  2018,  2018,  2027,
    2027,  2038,  2038,  2048,  2049,  2053,  2054,  2057,  2057,  2072,
    2072,  2082,  2082,  2093,  2094,  2098,  2102,  2102,  2114,  2115,
    2119,  2119,  2127,  2128,  2131,  2132,  2133,  2134,  2135,  2136,
    2137,  2140,  2145,  2145,  2153,  2153,  2163,  2164,  2167,  2167,
    2175,  2176,  2179,  2180,  2181,  2182,  2185,  2185,  2193,  2198,
    2203
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
#line 4843 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2208 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
