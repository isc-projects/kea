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
      case 223: // db_type
      case 302: // hr_mode
      case 373: // known_clients_value
      case 450: // ncr_protocol_value
      case 458: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 153: // "boolean"
        value.move< bool > (that.value);
        break;

      case 152: // "floating point"
        value.move< double > (that.value);
        break;

      case 151: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 150: // "constant string"
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
      case 223: // db_type
      case 302: // hr_mode
      case 373: // known_clients_value
      case 450: // ncr_protocol_value
      case 458: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 153: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 152: // "floating point"
        value.copy< double > (that.value);
        break;

      case 151: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 150: // "constant string"
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
            case 150: // "constant string"

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 151: // "integer"

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 152: // "floating point"

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 153: // "boolean"

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 389 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 168: // value

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 396 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 172: // map_value

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 403 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 210: // socket_type

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 410 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 213: // outbound_interface_value

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 417 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 223: // db_type

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 424 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 302: // hr_mode

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 431 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 373: // known_clients_value

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 438 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 450: // ncr_protocol_value

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 445 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 458: // replace_client_name_value

#line 229 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 452 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 223: // db_type
      case 302: // hr_mode
      case 373: // known_clients_value
      case 450: // ncr_protocol_value
      case 458: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 153: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 152: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 151: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 150: // "constant string"
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
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 262 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 263 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 293 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 315 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 324 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 333 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 348 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 363 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 387 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 509 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 521 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 522 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 527 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 538 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 556 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1228 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1280 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 637 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 642 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 652 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 667 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 674 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 679 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 695 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 705 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 710 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 725 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1593 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 783 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 788 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1614 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 806 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1623 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1641 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 821 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 826 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 831 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 868 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 890 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 894 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 932 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 942 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 958 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 964 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 966 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 972 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 974 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 982 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 988 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("eval-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1881 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1890 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 998 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1005 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1913 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1006 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1925 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1010 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 1022 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 1027 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1042 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 278:
#line 1046 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1076 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1081 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1089 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1108 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2040 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1123 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1157 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2089 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1172 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1174 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1180 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1190 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1192 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1207 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1235 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1247 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2210 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2218 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2228 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1308 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1327 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1333 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2296 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2314 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.KNOWN_CLIENTS);
}
#line 2349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("known-clients", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2358 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("only", ctx.loc2pos(yystack_[0].location))); }
#line 2364 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 388:
#line 1380 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location))); }
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2381 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2390 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2400 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1408 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2409 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1413 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2419 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2428 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2446 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2454 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1470 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2490 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2508 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2526 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2536 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2590 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2598 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1531 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1549 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2656 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1551 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2677 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1574 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2696 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1578 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("eval-on-demand", b);
}
#line 2733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2753 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1647 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2809 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2867 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1729 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2912 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2947 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2959 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1764 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3012 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1789 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3029 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1798 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1801 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3045 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1804 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1807 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1813 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1823 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3097 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3114 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1839 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3131 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3151 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1876 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1914 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3216 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1920 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3236 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1934 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1952 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1954 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1960 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3281 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1965 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1970 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3299 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3303 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -702;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     120,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,    29,    21,    24,    26,    35,    59,    84,
      93,    95,    97,   110,   125,   135,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
      21,   -10,     2,    28,   186,    39,   157,    73,   100,   136,
     193,   -58,   244,  -702,   150,   166,   173,   199,   213,  -702,
    -702,  -702,  -702,  -702,   251,  -702,    72,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,   267,   268,  -702,  -702,  -702,  -702,
    -702,   269,   298,   304,   305,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,   314,  -702,  -702,  -702,    90,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,   321,    91,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
     328,   329,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,   111,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   133,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,   209,   232,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   292,  -702,
    -702,   333,  -702,  -702,  -702,   335,  -702,  -702,   332,   249,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,   340,   343,  -702,  -702,  -702,  -702,   341,   345,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   141,
    -702,  -702,  -702,   365,  -702,  -702,   369,  -702,   370,   371,
    -702,  -702,   372,   373,   374,  -702,  -702,  -702,   184,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,    21,    21,  -702,   229,   376,
     377,   378,   379,   380,  -702,     2,  -702,   381,   233,   234,
     384,   385,   386,   387,   388,   242,   245,   246,   247,   391,
     395,   396,   397,   398,   399,   400,   401,   255,   403,   404,
      28,  -702,   405,   406,   407,   259,   186,  -702,   409,   410,
     411,   412,   413,   414,   415,   416,   270,   271,   418,   419,
     421,   422,   423,    39,  -702,   424,   425,   157,  -702,   426,
     427,   428,   429,   430,   431,   432,   433,  -702,    73,  -702,
     434,   435,   290,   436,   438,   439,   293,  -702,   136,   441,
     294,   297,  -702,   193,   444,   445,   -35,  -702,   300,   450,
     451,   306,   452,   309,   311,   459,   460,   312,   313,   315,
     463,   466,   244,  -702,  -702,  -702,   467,   465,   468,    21,
      21,    21,  -702,   469,  -702,  -702,   323,   324,   327,   471,
     472,  -702,  -702,  -702,  -702,   475,   476,   477,   478,   479,
     480,   481,   482,  -702,   483,   484,  -702,   487,    62,    67,
    -702,  -702,   338,   344,   346,   488,   490,   348,   349,   350,
    -702,  -702,    51,   487,   351,   497,   496,  -702,   354,   119,
    -702,   487,   355,   356,   357,   358,   359,   360,   361,  -702,
     362,   363,  -702,   364,   366,   367,  -702,  -702,   368,  -702,
    -702,  -702,   375,    21,  -702,  -702,   382,   383,  -702,   389,
    -702,  -702,    12,   393,  -702,  -702,  -702,   117,   390,  -702,
      21,    28,   392,  -702,  -702,  -702,   186,  -702,  -702,  -702,
     192,   192,   513,   514,   515,   516,   198,   517,   519,   179,
      96,   244,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,   520,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,   521,   440,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,   201,  -702,   207,  -702,  -702,   210,  -702,  -702,
    -702,  -702,   491,   525,   526,   530,   531,  -702,  -702,  -702,
     235,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,   285,  -702,   532,   533,  -702,  -702,
     535,   534,  -702,  -702,   536,   540,  -702,  -702,   538,   542,
    -702,  -702,  -702,  -702,  -702,  -702,    40,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,    41,  -702,  -702,   541,   543,  -702,
     544,   545,   546,   547,   548,   549,   286,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,   287,  -702,  -702,  -702,
     288,   408,  -702,   550,   551,  -702,  -702,   553,   552,  -702,
    -702,   554,  -702,   556,   392,  -702,  -702,   557,   559,   560,
     561,   336,   417,   420,   437,   442,   562,   563,   192,  -702,
    -702,    39,  -702,   513,   136,  -702,   514,   193,  -702,   515,
     124,  -702,   516,   198,  -702,   131,   517,  -702,   -58,  -702,
     519,   443,   446,   447,   448,   449,   453,   179,  -702,   564,
     565,    96,  -702,  -702,  -702,   566,   570,   157,  -702,   520,
      73,  -702,   521,   571,  -702,   569,  -702,   337,   455,   456,
     457,  -702,  -702,  -702,  -702,  -702,   458,   461,  -702,   289,
    -702,   568,  -702,   572,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,   295,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,   573,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,   574,   575,  -702,  -702,  -702,  -702,
    -702,   296,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
     462,   464,  -702,  -702,   470,   303,  -702,   576,  -702,   473,
     578,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,   124,  -702,   577,   474,  -702,   131,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   231,  -702,
    -702,   485,  -702,  -702,   -15,   578,  -702,  -702,  -702,   579,
    -702,  -702,  -702,   307,  -702,  -702,  -702,  -702,  -702,   582,
     486,   583,   -15,  -702,   584,  -702,   492,  -702,   581,  -702,
    -702,   248,  -702,   -65,   581,  -702,  -702,   587,   588,   591,
     319,  -702,  -702,  -702,  -702,  -702,  -702,   592,   494,   489,
     493,   -65,  -702,   495,  -702,  -702,  -702,  -702,  -702
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   108,     9,   220,    11,   370,    13,   397,    15,
     299,    17,   307,    19,   342,    21,   185,    23,   478,    25,
      43,    37,     0,     0,     0,     0,     0,   399,     0,   309,
     344,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     531,   525,   527,   529,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   100,     0,     0,   416,   418,   420,   121,
     123,     0,     0,     0,     0,   212,   297,   334,   271,   163,
     442,   177,   196,     0,   466,   476,    93,     0,    68,    70,
      71,    72,    73,    88,    89,    76,    77,    78,    79,    83,
      84,    74,    75,    81,    82,    90,    91,    92,    80,    85,
      86,    87,   110,   112,   116,     0,     0,   102,   104,   105,
     106,   107,   250,   252,   254,   362,   383,   248,   256,   258,
       0,     0,   264,   262,   260,   389,   438,   247,   224,   225,
     226,   239,     0,   222,   229,   243,   244,   245,   230,   231,
     234,   235,   237,   232,   233,   227,   228,   246,   236,   240,
     241,   242,   238,   381,   385,   380,   376,   377,   375,     0,
     372,   374,   378,   379,   436,   424,   426,   430,   428,   434,
     432,   422,   415,   411,     0,   400,   401,   412,   413,   414,
     408,   403,   409,   405,   406,   407,   410,   404,     0,   324,
     153,     0,   328,   326,   331,     0,   320,   321,     0,   310,
     311,   313,   323,   314,   315,   316,   330,   317,   318,   319,
     356,     0,     0,   354,   355,   358,   359,     0,   345,   346,
     348,   349,   350,   351,   352,   353,   192,   194,   189,     0,
     187,   190,   191,     0,   498,   500,     0,   503,     0,     0,
     507,   511,     0,     0,     0,   516,   523,   496,     0,   480,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,    42,     0,     0,    35,     0,     0,
       0,     0,     0,     0,    53,     0,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    67,     0,     0,     0,     0,     0,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   221,     0,     0,     0,   371,     0,
       0,     0,     0,     0,     0,     0,     0,   398,     0,   300,
       0,     0,     0,     0,     0,     0,     0,   308,     0,     0,
       0,     0,   343,     0,     0,     0,     0,   186,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   479,    46,    39,     0,     0,     0,     0,
       0,     0,    57,     0,    98,    99,     0,     0,     0,     0,
       0,    94,    95,    96,    97,     0,     0,     0,     0,     0,
       0,     0,     0,   465,     0,     0,    69,     0,     0,     0,
     120,   103,     0,     0,     0,     0,     0,     0,     0,     0,
     269,   270,     0,     0,     0,     0,     0,   223,     0,     0,
     373,     0,     0,     0,     0,     0,     0,     0,     0,   402,
       0,     0,   322,     0,     0,     0,   333,   312,     0,   360,
     361,   347,     0,     0,   188,   497,     0,     0,   502,     0,
     505,   506,     0,     0,   513,   514,   515,     0,     0,   481,
       0,     0,     0,   526,   528,   530,     0,   417,   419,   421,
       0,     0,   214,   301,   336,   273,     0,     0,   179,     0,
       0,     0,    47,   111,   114,   115,   113,   118,   119,   117,
     251,   253,   255,   364,    36,   384,   249,   257,   259,   266,
     267,   268,   265,   263,   261,   391,     0,   382,   387,   388,
     386,   437,   425,   427,   431,   429,   435,   433,   423,   325,
     154,   329,   327,   332,   357,   193,   195,   499,   501,   504,
     509,   510,   508,   512,   519,   518,   520,   521,   522,   517,
     524,    40,     0,   536,     0,   533,   535,     0,   140,   146,
     148,   150,     0,     0,     0,     0,     0,   159,   161,   139,
       0,   125,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,     0,   218,     0,   215,   216,   305,
       0,   302,   303,   340,     0,   337,   338,   277,     0,   274,
     275,   172,   173,   174,   175,   176,     0,   165,   167,   168,
     169,   170,   171,   446,     0,   444,   183,     0,   180,   181,
       0,     0,     0,     0,     0,     0,     0,   198,   200,   201,
     202,   203,   204,   205,   472,   474,     0,   468,   470,   471,
       0,    49,   368,     0,   365,   366,   395,     0,   392,   393,
     440,     0,    65,     0,     0,   532,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     124,     0,   213,     0,   309,   298,     0,   344,   335,     0,
       0,   272,     0,     0,   164,   448,     0,   443,     0,   178,
       0,     0,     0,     0,     0,     0,     0,     0,   197,     0,
       0,     0,   467,   477,    51,     0,    50,     0,   363,     0,
     399,   390,     0,     0,   439,     0,   534,     0,     0,     0,
       0,   152,   155,   156,   157,   158,     0,     0,   126,     0,
     217,     0,   304,     0,   339,   296,   295,   284,   285,   287,
     281,   282,   283,   293,   294,   292,     0,   279,   286,   288,
     289,   290,   291,   276,   166,   462,     0,   460,   461,   455,
     456,   457,   458,   459,     0,   449,   450,   452,   453,   454,
     445,     0,   182,   206,   207,   208,   209,   210,   211,   199,
       0,     0,   469,    48,     0,     0,   367,     0,   394,     0,
       0,   142,   143,   144,   145,   141,   147,   149,   151,   160,
     162,   219,   306,   341,     0,   278,     0,     0,   447,     0,
     184,   473,   475,    52,   369,   396,   441,   540,     0,   538,
     280,     0,   464,   451,     0,     0,   537,   463,   552,     0,
     550,   548,   544,     0,   542,   546,   547,   545,   539,     0,
       0,     0,     0,   541,     0,   549,     0,   543,     0,   551,
     556,     0,   554,     0,     0,   553,   564,     0,     0,     0,
       0,   558,   560,   561,   562,   563,   555,     0,     0,     0,
       0,     0,   557,     0,   566,   567,   568,   559,   565
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,   -49,  -702,   101,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -406,  -702,  -702,  -702,   -62,
    -702,  -702,  -702,   264,  -702,  -702,  -702,  -702,    92,   261,
     -51,   -40,   -27,  -702,  -702,   -25,  -702,  -702,    86,   263,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,    89,   -95,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,   -69,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -108,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -114,  -702,  -702,  -702,  -111,   222,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -118,  -702,  -702,  -702,  -702,  -702,  -702,
    -701,  -702,  -702,  -702,   -92,  -702,  -702,  -702,   -89,   262,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -679,  -702,
    -702,  -702,   -46,  -702,   -21,  -702,  -665,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,   -98,  -702,  -702,  -218,   -66,
    -702,  -702,  -702,  -702,  -702,   -88,  -702,  -702,  -702,   -85,
    -702,   243,  -702,   -64,  -702,  -702,  -702,  -702,  -702,   -52,
    -702,  -702,  -702,  -702,  -702,   -50,  -702,  -702,  -702,   -87,
    -702,  -702,  -702,   -84,  -702,   237,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -115,  -702,  -702,
    -702,  -109,   274,  -702,  -702,   -53,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -116,  -702,  -702,  -702,  -107,  -702,
     272,   -44,  -702,   -43,  -702,   -33,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -664,  -702,  -702,  -702,  -702,  -702,  -702,
     -72,  -702,  -702,  -702,  -192,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,   -79,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,   142,   252,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,   -22,  -702,  -702,  -702,
    -186,  -702,  -702,  -199,  -702,  -702,  -702,  -702,  -702,  -702,
    -205,  -702,  -702,  -221,  -702,  -702,  -702,  -702,  -702
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   545,    77,
      78,    37,    60,    74,    75,   533,   681,   745,   746,   116,
      39,    62,    86,    87,    88,   309,    41,    63,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   317,   146,   147,
      43,    64,   148,   342,   149,   343,   536,   150,   344,   539,
     151,   126,   323,   127,   324,   610,   611,   612,   697,   835,
     613,   698,   614,   699,   615,   700,   616,   237,   381,   618,
     619,   620,   621,   622,   706,   623,   707,   128,   333,   646,
     647,   648,   649,   650,   651,   652,   129,   335,   657,   658,
     659,   728,    57,    71,   269,   270,   271,   394,   272,   395,
     130,   336,   666,   667,   668,   669,   670,   671,   672,   673,
     131,   329,   626,   627,   628,   711,    45,    65,   172,   173,
     174,   353,   175,   348,   176,   349,   177,   350,   178,   354,
     179,   355,   180,   360,   181,   359,   182,   358,   552,   183,
     184,   132,   332,   638,   639,   640,   720,   786,   787,   133,
     330,    51,    68,   630,   631,   632,   714,    53,    69,   238,
     239,   240,   241,   242,   243,   244,   380,   245,   384,   246,
     383,   247,   248,   385,   249,   134,   331,   634,   635,   636,
     717,    55,    70,   257,   258,   259,   260,   261,   389,   262,
     263,   264,   265,   186,   351,   683,   684,   685,   747,    47,
      66,   199,   200,   201,   365,   187,   352,   203,   366,   560,
     188,   361,   687,   688,   689,   750,    49,    67,   214,   215,
     216,   135,   320,   136,   321,   137,   322,   220,   376,   221,
     370,   222,   371,   223,   373,   224,   372,   225,   375,   226,
     374,   227,   369,   192,   362,   691,   753,   138,   334,   654,
     655,   725,   804,   805,   806,   807,   808,   846,   809,   139,
     140,   338,   676,   677,   678,   739,   679,   740,   141,   339,
      59,    72,   288,   289,   290,   291,   399,   292,   400,   293,
     294,   402,   295,   296,   297,   405,   582,   298,   406,   299,
     300,   301,   302,   410,   589,   303,   411,    89,   311,    90,
     312,    91,   313,    92,   310,   594,   595,   596,   693,   858,
     859,   864,   873,   874,   875,   876,   881,   877,   879,   891,
     892,   893,   900,   901,   902,   907,   903,   904,   905
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   254,   228,   167,   195,   212,   255,   236,   253,   268,
     287,    73,    79,   202,   168,   185,   198,   213,   256,   781,
     196,   189,   190,   217,   218,   169,    27,   580,    28,    26,
      29,    38,   191,    40,   219,   266,   267,   230,   170,    93,
     171,   782,    42,   723,   726,   197,   724,   727,    94,    95,
      96,    97,    98,    99,   100,   785,   792,   553,   266,   267,
      95,    96,    97,    98,   896,   561,    44,   897,   898,   899,
     101,   102,   103,   104,   105,   315,   534,   535,   106,   107,
     316,   101,   102,   103,   537,   538,   152,   153,   154,   108,
     107,    46,    84,   340,   346,    96,    97,    98,   341,   347,
      48,   155,    50,   156,    52,   109,   110,   157,   158,   159,
     160,   161,   162,   868,   363,   869,   870,    54,   163,   364,
     111,   164,   165,   112,   107,   549,   550,   551,    80,   166,
     113,   114,    56,   581,   115,    84,   367,    81,    82,    83,
      76,   368,    58,   781,   396,    95,    96,    97,    98,   397,
     106,   204,    84,    96,    97,    98,   304,   205,   206,   207,
     208,   209,   210,   229,   211,   782,   101,   102,   103,   305,
     105,    30,    31,    32,    33,   107,   230,   306,    84,   785,
     792,   106,   107,   230,   584,   558,   559,   412,   230,    84,
     231,   232,   413,   158,   233,   234,   235,   162,   142,   143,
     674,   675,   144,   163,   340,   145,   164,   307,   107,   692,
     694,   795,   796,   346,   166,   695,   308,   377,   696,   598,
     193,   156,   194,    84,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   865,   378,   163,   866,   708,   164,
     585,   586,   587,   709,   230,   230,   250,   231,   232,   251,
     252,   894,   388,    85,   895,   314,   414,   415,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
     588,   318,   319,   325,    84,   660,   661,   662,   663,   664,
     665,    84,   641,   642,   643,   644,    84,   645,   708,   737,
     741,   412,   363,   710,   738,   742,   743,   841,   844,   396,
     379,   167,   326,   845,   850,   195,   367,    84,   327,   328,
     882,   854,   168,   185,   202,   883,   212,   198,   337,   189,
     190,   196,   911,   169,   254,   345,   236,   912,   213,   255,
     191,   253,   356,   357,   217,   218,   170,   382,   171,   386,
     387,   256,    84,    84,   390,   219,   197,   391,   393,   392,
     287,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   831,   832,   833,   834,   398,
     513,   514,   515,   401,   403,   404,   407,   408,   409,   416,
     417,   418,   419,   420,   421,   423,   424,   425,   426,   427,
     428,   429,   430,   431,    84,   435,   432,   433,   434,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   447,
     448,   449,   450,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   462,   463,   461,   464,   465,   466,   468,   469,
     471,   472,   473,   474,   475,   476,   477,   478,   480,   481,
     483,   482,   484,   485,   576,   488,   486,   489,   492,   493,
     490,   617,   617,   495,   496,   497,   499,   498,   609,   609,
     500,   591,   501,   502,   503,   504,   505,   507,   506,   287,
     508,   510,   511,   517,   518,   512,   516,   519,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   761,   540,   529,
     530,   531,   532,   543,   541,   701,   542,    28,   546,   547,
     548,   554,   555,   556,   557,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   583,   572,   573,   574,   593,
     625,   629,   633,   637,   653,   575,   656,   682,   686,   702,
     703,   690,   577,   578,   704,   705,   713,   716,   712,   579,
     590,   715,   718,   719,   721,   722,   730,   729,   731,   732,
     733,   734,   735,   736,   749,   752,   748,   544,   744,   751,
     755,   757,   754,   758,   759,   760,   766,   767,   820,   821,
     762,   763,   823,   824,   830,   829,   842,   847,   849,   422,
     843,   861,   848,   880,   855,   857,   884,   886,   890,   888,
     764,   908,   909,   765,   813,   910,   913,   814,   815,   816,
     817,   446,   597,   592,   818,   836,   837,   838,   839,   451,
     624,   840,   851,   768,   852,   794,   812,   811,   494,   819,
     853,   770,   769,   856,   793,   467,   860,   862,   772,   771,
     491,   487,   774,   773,   826,   867,   828,   885,   825,   617,
     915,   470,   889,   827,   916,   918,   609,   914,   254,   167,
     479,   780,   236,   255,   810,   253,   798,   863,   775,   799,
     168,   185,   822,   797,   509,   256,   268,   189,   190,   776,
     788,   169,   756,   680,   783,   800,   789,   790,   191,   878,
     777,   801,   802,   887,   170,   195,   171,   791,   212,   906,
     917,     0,   803,   778,   202,   779,     0,   198,     0,   784,
     213,   196,     0,     0,     0,     0,   217,   218,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   219,     0,     0,
       0,     0,     0,     0,     0,     0,   197,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   780,     0,     0,     0,     0,
     798,     0,   775,   799,     0,     0,     0,   797,     0,     0,
       0,     0,     0,   776,   788,   872,     0,     0,   783,   800,
     789,   790,   871,     0,   777,   801,   802,     0,     0,     0,
       0,   791,     0,   872,     0,     0,   803,   778,     0,   779,
     871,     0,     0,   784
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    68,    65,    66,    67,    70,    69,    70,    71,
      72,    60,    10,    66,    65,    65,    66,    67,    70,   720,
      66,    65,    65,    67,    67,    65,     5,    15,     7,     0,
       9,     7,    65,     7,    67,    93,    94,    52,    65,    11,
      65,   720,     7,     3,     3,    66,     6,     6,    20,    21,
      22,    23,    24,    25,    26,   720,   720,   463,    93,    94,
      21,    22,    23,    24,   129,   471,     7,   132,   133,   134,
      42,    43,    44,    45,    46,     3,    14,    15,    50,    51,
       8,    42,    43,    44,    17,    18,    47,    48,    49,    61,
      51,     7,   150,     3,     3,    22,    23,    24,     8,     8,
       7,    62,     7,    64,     7,    77,    78,    68,    69,    70,
      71,    72,    73,   128,     3,   130,   131,     7,    79,     8,
      92,    82,    83,    95,    51,    74,    75,    76,   126,    90,
     102,   103,     7,   121,   106,   150,     3,   135,   136,   137,
     150,     8,     7,   844,     3,    21,    22,    23,    24,     8,
      50,    78,   150,    22,    23,    24,     6,    84,    85,    86,
      87,    88,    89,    27,    91,   844,    42,    43,    44,     3,
      46,   150,   151,   152,   153,    51,    52,     4,   150,   844,
     844,    50,    51,    52,    67,    66,    67,     3,    52,   150,
      54,    55,     8,    69,    58,    59,    60,    73,    12,    13,
     104,   105,    16,    79,     3,    19,    82,     8,    51,     8,
       3,    80,    81,     3,    90,     8,     3,     8,     8,    27,
      63,    64,    65,   150,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     3,     3,    79,     6,     3,    82,
     123,   124,   125,     8,    52,    52,    53,    54,    55,    56,
      57,     3,     3,   315,     6,     4,   305,   306,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     153,     4,     4,     4,   150,    96,    97,    98,    99,   100,
     101,   150,    84,    85,    86,    87,   150,    89,     3,     3,
       3,     3,     3,     8,     8,     8,     8,     8,     3,     3,
       8,   363,     4,     8,     8,   367,     3,   150,     4,     4,
       3,     8,   363,   363,   367,     8,   378,   367,     4,   363,
     363,   367,     3,   363,   393,     4,   388,     8,   378,   393,
     363,   393,     4,     4,   378,   378,   363,     4,   363,     4,
       8,   393,   150,   150,     4,   378,   367,     4,     3,     8,
     412,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    28,    29,    30,    31,     4,
     419,   420,   421,     4,     4,     4,     4,     4,     4,   150,
       4,     4,     4,     4,     4,     4,   153,   153,     4,     4,
       4,     4,     4,   151,   150,     4,   151,   151,   151,     4,
       4,     4,     4,     4,     4,     4,   151,     4,     4,     4,
       4,     4,   153,     4,     4,     4,     4,     4,     4,     4,
       4,   151,     4,     4,   153,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   151,     4,     4,   493,     4,   153,   153,     4,     4,
     153,   520,   521,   153,     4,     4,     4,   151,   520,   521,
     151,   510,   151,     4,     4,   153,   153,     4,   153,   531,
       4,     4,     7,   150,   150,     7,     7,   150,     7,     7,
       5,     5,     5,     5,     5,     5,     5,   151,   150,     7,
       7,     7,     5,     5,   150,     4,   150,     7,   150,   150,
     150,   150,     5,     7,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   122,   150,   150,   150,   127,
       7,     7,     7,     7,     7,   150,     7,     7,     7,     4,
       4,    91,   150,   150,     4,     4,     3,     3,     6,   150,
     150,     6,     6,     3,     6,     3,     3,     6,     4,     4,
       4,     4,     4,     4,     3,     3,     6,   456,   150,     6,
       4,     4,     8,     4,     4,     4,     4,     4,     4,     4,
     153,   151,     6,     3,     5,     4,     8,     4,     3,   315,
       8,     4,     8,     4,     8,     7,     4,     4,     7,     5,
     153,     4,     4,   151,   151,     4,     4,   151,   151,   151,
     151,   340,   516,   511,   151,   150,   150,   150,   150,   346,
     521,   150,   150,   708,   150,   723,   730,   728,   396,   737,
     150,   713,   711,   150,   722,   363,   844,   153,   716,   714,
     393,   388,   719,   717,   749,   150,   752,   151,   747,   708,
     151,   367,   150,   750,   151,   150,   708,   153,   717,   711,
     378,   720,   714,   717,   726,   717,   725,   849,   720,   725,
     711,   711,   741,   725,   412,   717,   728,   711,   711,   720,
     720,   711,   694,   531,   720,   725,   720,   720,   711,   865,
     720,   725,   725,   882,   711,   747,   711,   720,   750,   894,
     911,    -1,   725,   720,   747,   720,    -1,   747,    -1,   720,
     750,   747,    -1,    -1,    -1,    -1,   750,   750,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   750,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   747,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   844,    -1,    -1,    -1,    -1,
     849,    -1,   844,   849,    -1,    -1,    -1,   849,    -1,    -1,
      -1,    -1,    -1,   844,   844,   864,    -1,    -1,   844,   849,
     844,   844,   864,    -1,   844,   849,   849,    -1,    -1,    -1,
      -1,   844,    -1,   882,    -1,    -1,   849,   844,    -1,   844,
     882,    -1,    -1,   844
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,     0,     5,     7,     9,
     150,   151,   152,   153,   168,   169,   170,   175,     7,   184,
       7,   190,     7,   204,     7,   280,     7,   363,     7,   380,
       7,   315,     7,   321,     7,   345,     7,   256,     7,   434,
     176,   171,   185,   191,   205,   281,   364,   381,   316,   322,
     346,   257,   435,   168,   177,   178,   150,   173,   174,    10,
     126,   135,   136,   137,   150,   183,   186,   187,   188,   461,
     463,   465,   467,    11,    20,    21,    22,    23,    24,    25,
      26,    42,    43,    44,    45,    46,    50,    51,    61,    77,
      78,    92,    95,   102,   103,   106,   183,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   215,   217,   241,   250,
     264,   274,   305,   313,   339,   385,   387,   389,   411,   423,
     424,   432,    12,    13,    16,    19,   202,   203,   206,   208,
     211,   214,    47,    48,    49,    62,    64,    68,    69,    70,
      71,    72,    73,    79,    82,    83,    90,   183,   194,   195,
     196,   199,   282,   283,   284,   286,   288,   290,   292,   294,
     296,   298,   300,   303,   304,   339,   357,   369,   374,   385,
     387,   389,   407,    63,    65,   183,   296,   298,   339,   365,
     366,   367,   369,   371,    78,    84,    85,    86,    87,    88,
      89,    91,   183,   339,   382,   383,   384,   385,   387,   389,
     391,   393,   395,   397,   399,   401,   403,   405,   313,    27,
      52,    54,    55,    58,    59,    60,   183,   231,   323,   324,
     325,   326,   327,   328,   329,   331,   333,   335,   336,   338,
      53,    56,    57,   183,   231,   327,   333,   347,   348,   349,
     350,   351,   353,   354,   355,   356,    93,    94,   183,   258,
     259,   260,   262,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   183,   436,   437,
     438,   439,   441,   443,   444,   446,   447,   448,   451,   453,
     454,   455,   456,   459,     6,     3,     4,     8,     3,   189,
     468,   462,   464,   466,     4,     3,     8,   201,     4,     4,
     386,   388,   390,   216,   218,     4,     4,     4,     4,   275,
     314,   340,   306,   242,   412,   251,   265,     4,   425,   433,
       3,     8,   207,   209,   212,     4,     3,     8,   287,   289,
     291,   358,   370,   285,   293,   295,     4,     4,   301,   299,
     297,   375,   408,     3,     8,   368,   372,     3,     8,   406,
     394,   396,   400,   398,   404,   402,   392,     8,     3,     8,
     330,   232,     4,   334,   332,   337,     4,     8,     3,   352,
       4,     4,     8,     3,   261,   263,     3,     8,     4,   440,
     442,     4,   445,     4,     4,   449,   452,     4,     4,     4,
     457,   460,     3,     8,   168,   168,   150,     4,     4,     4,
       4,     4,   187,     4,   153,   153,     4,     4,     4,     4,
       4,   151,   151,   151,   151,     4,     4,     4,     4,     4,
       4,     4,     4,   151,     4,     4,   193,     4,     4,     4,
     153,   203,     4,     4,     4,     4,     4,     4,     4,     4,
     151,   153,     4,     4,     4,     4,     4,   283,     4,     4,
     366,     4,     4,     4,     4,     4,     4,     4,     4,   384,
       4,     4,   151,     4,     4,     4,   153,   325,     4,   153,
     153,   349,     4,     4,   259,   153,     4,     4,   151,     4,
     151,   151,     4,     4,   153,   153,   153,     4,     4,   437,
       4,     7,     7,   168,   168,   168,     7,   150,   150,   150,
       7,     7,     5,     5,     5,     5,     5,     5,     5,     7,
       7,     7,     5,   179,    14,    15,   210,    17,    18,   213,
     150,   150,   150,     5,   170,   172,   150,   150,   150,    74,
      75,    76,   302,   179,   150,     5,     7,   150,    66,    67,
     373,   179,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   168,   150,   150,   150,
      15,   121,   450,   122,    67,   123,   124,   125,   153,   458,
     150,   168,   192,   127,   469,   470,   471,   202,    27,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,   183,
     219,   220,   221,   224,   226,   228,   230,   231,   233,   234,
     235,   236,   237,   239,   219,     7,   276,   277,   278,     7,
     317,   318,   319,     7,   341,   342,   343,     7,   307,   308,
     309,    84,    85,    86,    87,    89,   243,   244,   245,   246,
     247,   248,   249,     7,   413,   414,     7,   252,   253,   254,
      96,    97,    98,    99,   100,   101,   266,   267,   268,   269,
     270,   271,   272,   273,   104,   105,   426,   427,   428,   430,
     436,   180,     7,   359,   360,   361,     7,   376,   377,   378,
      91,   409,     8,   472,     3,     8,     8,   222,   225,   227,
     229,     4,     4,     4,     4,     4,   238,   240,     3,     8,
       8,   279,     6,     3,   320,     6,     3,   344,     6,     3,
     310,     6,     3,     3,     6,   415,     3,     6,   255,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   429,
     431,     3,     8,     8,   150,   181,   182,   362,     6,     3,
     379,     6,     3,   410,     8,     4,   470,     4,     4,     4,
       4,   151,   153,   151,   153,   151,     4,     4,   220,   282,
     278,   323,   319,   347,   343,   183,   194,   195,   196,   199,
     231,   274,   292,   296,   298,   300,   311,   312,   339,   385,
     387,   389,   407,   309,   244,    80,    81,   183,   231,   313,
     339,   385,   387,   389,   416,   417,   418,   419,   420,   422,
     414,   258,   254,   151,   151,   151,   151,   151,   151,   267,
       4,     4,   427,     6,     3,   365,   361,   382,   378,     4,
       5,    28,    29,    30,    31,   223,   150,   150,   150,   150,
     150,     8,     8,     8,     3,     8,   421,     4,     8,     3,
       8,   150,   150,   150,     8,     8,   150,     7,   473,   474,
     312,     4,   153,   418,   475,     3,     6,   150,   128,   130,
     131,   183,   231,   476,   477,   478,   479,   481,   474,   482,
       4,   480,     3,     8,     4,   151,     4,   477,     5,   150,
       7,   483,   484,   485,     3,     6,   129,   132,   133,   134,
     486,   487,   488,   490,   491,   492,   484,   489,     4,     4,
       4,     3,     8,     4,   153,   151,   151,   487,   150
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   154,   156,   155,   157,   155,   158,   155,   159,   155,
     160,   155,   161,   155,   162,   155,   163,   155,   164,   155,
     165,   155,   166,   155,   167,   155,   168,   168,   168,   168,
     168,   168,   168,   169,   171,   170,   172,   173,   173,   174,
     174,   176,   175,   177,   177,   178,   178,   180,   179,   181,
     181,   182,   182,   183,   185,   184,   186,   186,   187,   187,
     187,   187,   187,   187,   189,   188,   191,   190,   192,   192,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   194,   195,   196,   197,   198,   199,
     201,   200,   202,   202,   203,   203,   203,   203,   205,   204,
     207,   206,   209,   208,   210,   210,   212,   211,   213,   213,
     214,   216,   215,   218,   217,   219,   219,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     222,   221,   223,   223,   223,   223,   225,   224,   227,   226,
     229,   228,   230,   232,   231,   233,   234,   235,   236,   238,
     237,   240,   239,   242,   241,   243,   243,   244,   244,   244,
     244,   244,   245,   246,   247,   248,   249,   251,   250,   252,
     252,   253,   253,   255,   254,   257,   256,   258,   258,   258,
     259,   259,   261,   260,   263,   262,   265,   264,   266,   266,
     267,   267,   267,   267,   267,   267,   268,   269,   270,   271,
     272,   273,   275,   274,   276,   276,   277,   277,   279,   278,
     281,   280,   282,   282,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   285,   284,
     287,   286,   289,   288,   291,   290,   293,   292,   295,   294,
     297,   296,   299,   298,   301,   300,   302,   302,   302,   303,
     304,   306,   305,   307,   307,   308,   308,   310,   309,   311,
     311,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   314,   313,   316,
     315,   317,   317,   318,   318,   320,   319,   322,   321,   323,
     323,   324,   324,   325,   325,   325,   325,   325,   325,   325,
     325,   326,   327,   328,   330,   329,   332,   331,   334,   333,
     335,   337,   336,   338,   340,   339,   341,   341,   342,   342,
     344,   343,   346,   345,   347,   347,   348,   348,   349,   349,
     349,   349,   349,   349,   349,   350,   352,   351,   353,   354,
     355,   356,   358,   357,   359,   359,   360,   360,   362,   361,
     364,   363,   365,   365,   366,   366,   366,   366,   366,   366,
     366,   368,   367,   370,   369,   372,   371,   373,   373,   375,
     374,   376,   376,   377,   377,   379,   378,   381,   380,   382,
     382,   383,   383,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   386,   385,   388,   387,
     390,   389,   392,   391,   394,   393,   396,   395,   398,   397,
     400,   399,   402,   401,   404,   403,   406,   405,   408,   407,
     410,   409,   412,   411,   413,   413,   415,   414,   416,   416,
     417,   417,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   419,   421,   420,   422,   423,   425,   424,   426,   426,
     427,   427,   429,   428,   431,   430,   433,   432,   435,   434,
     436,   436,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   438,   440,   439,
     442,   441,   443,   445,   444,   446,   447,   449,   448,   450,
     450,   452,   451,   453,   454,   455,   457,   456,   458,   458,
     458,   458,   458,   460,   459,   462,   461,   464,   463,   466,
     465,   468,   467,   469,   469,   470,   472,   471,   473,   473,
     475,   474,   476,   476,   477,   477,   477,   477,   477,   478,
     480,   479,   482,   481,   483,   483,   485,   484,   486,   486,
     487,   487,   487,   487,   489,   488,   490,   491,   492
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
       1,     0,     4,     0,     4,     0,     4,     1,     1,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     0,     6,     1,     3,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"known-clients\"", "\"only\"", "\"never\"", "\"subnet\"",
  "\"interface\"", "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"eval-client-classes\"", "\"test\"", "\"eval-on-demand\"",
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
  "\"when-present\"", "\"always\"", "\"when-not-present\"", "\"Logging\"",
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
  "$@48", "client_class", "$@49", "eval_client_classes", "$@50",
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
  "$@70", "known_clients", "$@71", "known_clients_value", "reservations",
  "$@72", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@73", "sub_reservation", "$@74", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@75", "server_hostname", "$@76", "boot_file_name", "$@77",
  "ip_address", "$@78", "duid", "$@79", "hw_address", "$@80",
  "client_id_value", "$@81", "circuit_id_value", "$@82", "flex_id_value",
  "$@83", "hostname", "$@84", "reservation_client_classes", "$@85",
  "relay", "$@86", "relay_map", "$@87", "client_classes", "$@88",
  "client_classes_list", "client_class_entry", "$@89",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@90",
  "eval_on_demand", "dhcp4o6_port", "control_socket", "$@91",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@92", "control_socket_name", "$@93", "dhcp_ddns", "$@94",
  "sub_dhcp_ddns", "$@95", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@96", "server_ip", "$@97",
  "server_port", "sender_ip", "$@98", "sender_port", "max_queue_size",
  "ncr_protocol", "$@99", "ncr_protocol_value", "ncr_format", "$@100",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@101", "replace_client_name_value",
  "generated_prefix", "$@102", "dhcp6_json_object", "$@103",
  "dhcpddns_json_object", "$@104", "control_agent_json_object", "$@105",
  "logging_object", "$@106", "logging_params", "logging_param", "loggers",
  "$@107", "loggers_entries", "logger_entry", "$@108", "logger_params",
  "logger_param", "debuglevel", "severity", "$@109", "output_options_list",
  "$@110", "output_options_list_content", "output_entry", "$@111",
  "output_params_list", "output_params", "output", "$@112", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   238,   238,   238,   239,   239,   240,   240,   241,   241,
     242,   242,   243,   243,   244,   244,   245,   245,   246,   246,
     247,   247,   248,   248,   249,   249,   257,   258,   259,   260,
     261,   262,   263,   266,   271,   271,   282,   285,   286,   289,
     293,   300,   300,   307,   308,   311,   315,   322,   322,   329,
     330,   333,   337,   348,   358,   358,   374,   375,   379,   380,
     381,   382,   383,   384,   387,   387,   402,   402,   411,   412,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   443,   448,   453,   458,   463,   468,
     474,   474,   485,   486,   489,   490,   491,   492,   495,   495,
     504,   504,   514,   514,   521,   522,   525,   525,   532,   534,
     538,   544,   544,   556,   556,   568,   569,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     587,   587,   594,   595,   596,   597,   600,   600,   608,   608,
     616,   616,   624,   629,   629,   637,   642,   647,   652,   657,
     657,   665,   665,   674,   674,   684,   685,   688,   689,   690,
     691,   692,   695,   700,   705,   710,   715,   720,   720,   730,
     731,   734,   735,   738,   738,   748,   748,   758,   759,   760,
     763,   764,   767,   767,   775,   775,   783,   783,   794,   795,
     798,   799,   800,   801,   802,   803,   806,   811,   816,   821,
     826,   831,   839,   839,   852,   853,   856,   857,   864,   864,
     890,   890,   901,   902,   906,   907,   908,   909,   910,   911,
     912,   913,   914,   915,   916,   917,   918,   919,   920,   921,
     922,   923,   924,   925,   926,   927,   928,   929,   932,   932,
     940,   940,   948,   948,   956,   956,   964,   964,   972,   972,
     980,   980,   988,   988,   998,   998,  1005,  1006,  1007,  1010,
    1015,  1022,  1022,  1033,  1034,  1038,  1039,  1042,  1042,  1050,
    1051,  1054,  1055,  1056,  1057,  1058,  1059,  1060,  1061,  1062,
    1063,  1064,  1065,  1066,  1067,  1068,  1069,  1076,  1076,  1089,
    1089,  1098,  1099,  1102,  1103,  1108,  1108,  1123,  1123,  1137,
    1138,  1141,  1142,  1145,  1146,  1147,  1148,  1149,  1150,  1151,
    1152,  1155,  1157,  1162,  1164,  1164,  1172,  1172,  1180,  1180,
    1188,  1190,  1190,  1198,  1207,  1207,  1219,  1220,  1225,  1226,
    1231,  1231,  1243,  1243,  1255,  1256,  1261,  1262,  1267,  1268,
    1269,  1270,  1271,  1272,  1273,  1276,  1278,  1278,  1286,  1288,
    1290,  1295,  1303,  1303,  1315,  1316,  1319,  1320,  1323,  1323,
    1333,  1333,  1343,  1344,  1347,  1348,  1349,  1350,  1351,  1352,
    1353,  1356,  1356,  1364,  1364,  1371,  1371,  1379,  1380,  1386,
    1386,  1396,  1397,  1400,  1401,  1404,  1404,  1413,  1413,  1422,
    1423,  1426,  1427,  1431,  1432,  1433,  1434,  1435,  1436,  1437,
    1438,  1439,  1440,  1441,  1442,  1443,  1446,  1446,  1454,  1454,
    1462,  1462,  1470,  1470,  1478,  1478,  1486,  1486,  1494,  1494,
    1502,  1502,  1510,  1510,  1518,  1518,  1526,  1526,  1539,  1539,
    1549,  1549,  1560,  1560,  1570,  1571,  1574,  1574,  1584,  1585,
    1588,  1589,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,
    1600,  1603,  1605,  1605,  1613,  1622,  1629,  1629,  1639,  1640,
    1643,  1644,  1647,  1647,  1655,  1655,  1665,  1665,  1677,  1677,
    1687,  1688,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,
    1699,  1700,  1701,  1702,  1703,  1704,  1705,  1708,  1713,  1713,
    1721,  1721,  1729,  1734,  1734,  1742,  1747,  1752,  1752,  1760,
    1761,  1764,  1764,  1772,  1777,  1782,  1787,  1787,  1795,  1798,
    1801,  1804,  1807,  1813,  1813,  1823,  1823,  1830,  1830,  1837,
    1837,  1849,  1849,  1862,  1863,  1867,  1871,  1871,  1883,  1884,
    1888,  1888,  1896,  1897,  1900,  1901,  1902,  1903,  1904,  1907,
    1912,  1912,  1920,  1920,  1930,  1931,  1934,  1934,  1942,  1943,
    1946,  1947,  1948,  1949,  1952,  1952,  1960,  1965,  1970
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
#line 4461 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1975 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
