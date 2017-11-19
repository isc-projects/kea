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
      case 298: // hr_mode
      case 369: // known_clients_value
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
      case 298: // hr_mode
      case 369: // known_clients_value
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

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 368 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 149: // "integer"

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 375 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 150: // "floating point"

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 382 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 151: // "boolean"

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 389 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 166: // value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 396 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 170: // map_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 403 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 208: // socket_type

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 410 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 211: // outbound_interface_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 417 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 221: // db_type

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 424 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 298: // hr_mode

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 431 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 369: // known_clients_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 438 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 445: // ncr_protocol_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 445 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 453: // replace_client_name_value

#line 227 "dhcp4_parser.yy" // lalr1.cc:636
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
      case 166: // value
      case 170: // map_value
      case 208: // socket_type
      case 211: // outbound_interface_value
      case 221: // db_type
      case 298: // hr_mode
      case 369: // known_clients_value
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
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 700 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 706 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 712 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 239 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 718 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 240 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 241 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 242 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 736 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 243 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 742 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 244 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 245 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 754 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 760 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 778 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 790 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 796 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 808 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 817 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 844 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 287 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 853 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 915 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 335 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 944 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 955 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 361 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 385 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1001 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1010 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1028 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1037 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 456 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 461 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 466 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1064 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 472 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1075 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 477 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 493 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 514 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1141 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1147 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 520 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1153 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 532 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1206 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1228 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 585 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 587 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 593 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1268 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1274 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 595 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1280 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1288 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1298 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1316 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 614 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 616 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 629 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 635 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1379 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1388 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1397 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1405 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1415 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 663 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 672 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1453 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 172:
#line 693 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 173:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1471 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1509 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 740 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1548 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 750 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1558 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 765 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1566 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1576 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 773 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1584 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1593 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1604 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1614 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1623 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 207:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1641 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 862 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
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
#line 1724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 888 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1744 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1788 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1806 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 971 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1852 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 979 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1870 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 992 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1893 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1899 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 994 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 1009 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1029 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1953 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1033 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1961 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 293:
#line 1062 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1972 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1067 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1990 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1078 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1998 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1098 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2020 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1109 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2069 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2077 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2087 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2095 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 327:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 328:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 329:
#line 1184 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1217 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2171 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 338:
#line 1229 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1233 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1266 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2226 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2237 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1294 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1309 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2256 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2266 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1319 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1323 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2286 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.KNOWN_CLIENTS);
}
#line 2329 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1358 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("known-clients", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("only", ctx.loc2pos(yystack_[0].location))); }
#line 2344 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location))); }
#line 2350 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1371 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1376 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2370 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1389 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2380 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2389 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1398 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2399 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1402 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2408 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1431 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2416 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1439 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2434 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2444 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2452 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2462 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2470 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2488 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2498 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2516 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1487 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2552 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1495 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2570 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2588 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1511 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2599 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1516 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1524 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1529 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2657 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1591 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2713 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1608 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2724 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2733 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 465:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1628 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2751 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2811 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1687 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1692 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1694 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1702 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2865 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2873 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2892 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2909 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2924 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1743 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2938 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2966 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2983 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1768 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2992 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1774 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3008 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1783 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1786 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1802 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3059 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3076 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1811 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1816 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3093 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1850 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1855 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1886 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3169 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3187 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1904 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1913 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3225 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1944 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3270 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3274 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -703;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     126,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,    30,    22,    21,    37,    51,    76,   102,
     112,   116,   124,   141,   152,   167,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
      22,   -67,    -8,    28,    91,   113,    -4,   127,   150,    87,
      43,   -36,   171,  -703,   209,   199,   217,   211,   235,  -703,
    -703,  -703,  -703,  -703,   247,  -703,    35,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,   270,   294,  -703,  -703,  -703,  -703,
    -703,   296,   304,   306,   307,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,   310,  -703,  -703,  -703,    54,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,   326,    72,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
     332,   349,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,    74,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,   105,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,   250,   289,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,   315,  -703,  -703,   350,  -703,
    -703,  -703,   351,  -703,  -703,   348,   354,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,   355,   356,
    -703,  -703,  -703,  -703,   353,   359,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,   135,  -703,  -703,  -703,
     360,  -703,  -703,   361,  -703,   362,   363,  -703,  -703,   367,
     368,   369,  -703,  -703,  -703,   184,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,    22,    22,  -703,   210,   370,   371,   372,   373,
     374,  -703,    -8,  -703,   375,   212,   229,   377,   378,   379,
     380,   381,   237,   238,   239,   240,   386,   387,   388,   389,
     390,   391,   392,   393,   251,   394,   395,    28,  -703,   397,
     398,   399,   253,    91,  -703,   401,   402,   403,   404,   405,
     406,   407,   408,   264,   263,   411,   412,   413,   414,   113,
    -703,   415,   416,    -4,  -703,   417,   418,   419,   420,   421,
     422,   423,   424,  -703,   127,  -703,   425,   426,   282,   428,
     429,   430,   284,  -703,    87,   432,   286,   292,  -703,    43,
     434,   435,    10,  -703,   293,   436,   438,   299,   441,   300,
     301,   447,   448,   305,   308,   309,   451,   453,   171,  -703,
    -703,  -703,   457,   455,   456,    22,    22,    22,  -703,   458,
    -703,  -703,   320,   321,   322,   459,   460,  -703,  -703,  -703,
    -703,   466,   467,   468,   469,   470,   471,   472,   473,  -703,
     474,   475,  -703,   478,   151,   162,  -703,  -703,   331,   337,
     338,   479,   480,   340,   341,   342,  -703,  -703,    -7,   343,
     487,   486,  -703,   346,   122,  -703,   478,   347,   352,   357,
     358,   364,   365,   366,  -703,   376,   382,  -703,   383,   384,
     385,  -703,  -703,   396,  -703,  -703,  -703,   400,    22,  -703,
    -703,   409,   410,  -703,   427,  -703,  -703,     5,   431,  -703,
    -703,  -703,    85,   433,  -703,    22,    28,   437,  -703,  -703,
    -703,    91,  -703,  -703,  -703,   193,   193,   489,   490,   491,
     492,   159,   494,   495,   208,   249,   171,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,   496,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,   497,
     439,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,   195,  -703,   196,  -703,
    -703,   214,  -703,  -703,  -703,  -703,   503,   504,   505,   506,
     507,  -703,  -703,  -703,   215,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,   244,  -703,
     509,   513,  -703,  -703,   511,   515,  -703,  -703,   514,   516,
    -703,  -703,   517,   518,  -703,  -703,  -703,  -703,  -703,  -703,
       8,  -703,  -703,  -703,  -703,  -703,  -703,  -703,    39,  -703,
    -703,   519,   523,  -703,   525,   530,   531,   532,   533,   534,
     245,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
     246,  -703,  -703,  -703,   287,   440,  -703,   521,   536,  -703,
    -703,   535,   537,  -703,  -703,   538,  -703,   539,   437,  -703,
    -703,   541,   543,   545,   546,   329,   442,   443,   444,   445,
     548,   549,   193,  -703,  -703,   113,  -703,   489,    87,  -703,
     490,    43,  -703,   491,    42,  -703,   492,   159,  -703,   145,
     494,  -703,   -36,  -703,   495,   449,   450,   452,   454,   461,
     462,   208,  -703,   550,   551,   249,  -703,  -703,  -703,   553,
     557,    -4,  -703,   496,   127,  -703,   497,   552,  -703,   556,
    -703,   319,   464,   465,   476,  -703,  -703,  -703,  -703,  -703,
     477,   481,  -703,   288,  -703,   555,  -703,   558,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,   291,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,   559,   561,  -703,  -703,
    -703,  -703,   318,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,   482,   483,  -703,  -703,   484,   330,  -703,   560,  -703,
     488,   562,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,    42,  -703,   566,  -703,   145,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,   114,  -703,
    -703,   493,  -703,   111,   562,  -703,  -703,  -703,   567,  -703,
    -703,  -703,   334,  -703,  -703,  -703,  -703,  -703,   568,   485,
     569,   111,  -703,   571,  -703,   500,  -703,   570,  -703,  -703,
     254,  -703,   -40,   570,  -703,  -703,   574,   575,   576,   336,
    -703,  -703,  -703,  -703,  -703,  -703,   578,   446,   502,   510,
     -40,  -703,   508,  -703,  -703,  -703,  -703,  -703
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   108,     9,   220,    11,   366,    13,   392,    15,
     295,    17,   303,    19,   338,    21,   185,    23,   471,    25,
      43,    37,     0,     0,     0,     0,     0,   394,     0,   305,
     340,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     524,   518,   520,   522,     0,    63,     0,    56,    58,    60,
      61,    62,    59,   100,     0,     0,   411,   413,   415,   121,
     123,     0,     0,     0,     0,   212,   293,   330,   268,   163,
     437,   177,   196,     0,   459,   469,    93,     0,    68,    70,
      71,    72,    73,    88,    89,    76,    77,    78,    79,    83,
      84,    74,    75,    81,    82,    90,    91,    92,    80,    85,
      86,    87,   110,   112,   116,     0,     0,   102,   104,   105,
     106,   107,   249,   251,   253,   358,   378,   247,   255,   257,
       0,     0,   261,   259,   384,   433,   246,   224,   225,   226,
     238,     0,   222,   229,   242,   243,   244,   230,   231,   234,
     236,   232,   233,   227,   228,   245,   235,   239,   240,   241,
     237,   376,   380,   375,   372,   371,     0,   368,   370,   373,
     374,   431,   419,   421,   425,   423,   429,   427,   417,   410,
     406,     0,   395,   396,   407,   408,   409,   403,   398,   404,
     400,   401,   402,   405,   399,     0,   320,   153,     0,   324,
     322,   327,     0,   316,   317,     0,   306,   307,   309,   319,
     310,   311,   312,   326,   313,   314,   315,   352,     0,     0,
     350,   351,   354,   355,     0,   341,   342,   344,   345,   346,
     347,   348,   349,   192,   194,   189,     0,   187,   190,   191,
       0,   491,   493,     0,   496,     0,     0,   500,   504,     0,
       0,     0,   509,   516,   489,     0,   473,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,    42,     0,     0,    35,     0,     0,     0,     0,     0,
       0,    53,     0,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     221,     0,     0,     0,   367,     0,     0,     0,     0,     0,
       0,     0,     0,   393,     0,   296,     0,     0,     0,     0,
       0,     0,     0,   304,     0,     0,     0,     0,   339,     0,
       0,     0,     0,   186,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   472,
      46,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      98,    99,     0,     0,     0,     0,     0,    94,    95,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,   458,
       0,     0,    69,     0,     0,     0,   120,   103,     0,     0,
       0,     0,     0,     0,     0,     0,   266,   267,     0,     0,
       0,     0,   223,     0,     0,   369,     0,     0,     0,     0,
       0,     0,     0,     0,   397,     0,     0,   318,     0,     0,
       0,   329,   308,     0,   356,   357,   343,     0,     0,   188,
     490,     0,     0,   495,     0,   498,   499,     0,     0,   506,
     507,   508,     0,     0,   474,     0,     0,     0,   519,   521,
     523,     0,   412,   414,   416,     0,     0,   214,   297,   332,
     270,     0,     0,   179,     0,     0,     0,    47,   111,   114,
     115,   113,   118,   119,   117,   250,   252,   254,   360,    36,
     379,   248,   256,   258,   263,   264,   265,   262,   260,   386,
       0,   377,   382,   383,   381,   432,   420,   422,   426,   424,
     430,   428,   418,   321,   154,   325,   323,   328,   353,   193,
     195,   492,   494,   497,   502,   503,   501,   505,   512,   511,
     513,   514,   515,   510,   517,    40,     0,   529,     0,   526,
     528,     0,   140,   146,   148,   150,     0,     0,     0,     0,
       0,   159,   161,   139,     0,   125,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,     0,   218,
       0,   215,   216,   301,     0,   298,   299,   336,     0,   333,
     334,   274,     0,   271,   272,   172,   173,   174,   175,   176,
       0,   165,   167,   168,   169,   170,   171,   441,     0,   439,
     183,     0,   180,   181,     0,     0,     0,     0,     0,     0,
       0,   198,   200,   201,   202,   203,   204,   205,   465,   467,
       0,   461,   463,   464,     0,    49,   364,     0,   361,   362,
     390,     0,   387,   388,   435,     0,    65,     0,     0,   525,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   122,   124,     0,   213,     0,   305,   294,
       0,   340,   331,     0,     0,   269,     0,     0,   164,   443,
       0,   438,     0,   178,     0,     0,     0,     0,     0,     0,
       0,     0,   197,     0,     0,     0,   460,   470,    51,     0,
      50,     0,   359,     0,   394,   385,     0,     0,   434,     0,
     527,     0,     0,     0,     0,   152,   155,   156,   157,   158,
       0,     0,   126,     0,   217,     0,   300,     0,   335,   292,
     291,   281,   282,   284,   278,   279,   280,   290,   289,     0,
     276,   283,   285,   286,   287,   288,   273,   166,   456,   454,
     455,   449,   450,   451,   452,   453,     0,   444,   445,   447,
     448,   440,     0,   182,   206,   207,   208,   209,   210,   211,
     199,     0,     0,   462,    48,     0,     0,   363,     0,   389,
       0,     0,   142,   143,   144,   145,   141,   147,   149,   151,
     160,   162,   219,   302,   337,     0,   275,     0,   442,     0,
     184,   466,   468,    52,   365,   391,   436,   533,     0,   531,
     277,     0,   446,     0,     0,   530,   457,   545,     0,   543,
     541,   537,     0,   535,   539,   540,   538,   532,     0,     0,
       0,     0,   534,     0,   542,     0,   536,     0,   544,   549,
       0,   547,     0,     0,   546,   557,     0,     0,     0,     0,
     551,   553,   554,   555,   556,   548,     0,     0,     0,     0,
       0,   550,     0,   559,   560,   561,   552,   558
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,   -47,  -703,    70,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,    99,  -703,  -703,  -703,   -62,
    -703,  -703,  -703,   230,  -703,  -703,  -703,  -703,    68,   248,
     -30,   -25,   -24,  -703,  -703,   -19,  -703,  -703,    73,   243,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,    67,  -115,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,   -69,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -128,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -134,  -703,  -703,  -703,  -131,   204,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -129,  -703,  -703,  -703,  -703,  -703,  -703,
    -702,  -703,  -703,  -703,  -107,  -703,  -703,  -703,  -101,   255,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -682,  -703,
    -703,  -703,   -48,  -703,  -681,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -111,  -703,  -703,  -229,   -49,  -703,  -703,
    -703,  -703,  -703,  -103,  -703,  -703,  -703,  -100,  -703,   225,
    -703,   -64,  -703,  -703,  -703,  -703,  -703,   -44,  -703,  -703,
    -703,  -703,  -703,   -50,  -703,  -703,  -703,   -98,  -703,  -703,
    -703,   -95,  -703,   228,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -125,  -703,  -703,  -703,  -122,
     257,  -703,  -703,   -45,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -124,  -703,  -703,  -703,  -123,  -703,   252,   -43,
    -703,   -42,  -703,   -31,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -677,  -703,  -703,  -703,  -703,  -703,  -703,   -97,  -703,
    -703,  -703,  -212,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
     -96,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,   109,
     220,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,   -51,  -703,  -703,  -703,  -216,  -703,  -703,
    -227,  -703,  -703,  -703,  -703,  -703,  -703,  -230,  -703,  -703,
    -246,  -703,  -703,  -703,  -703,  -703
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    34,    35,    36,    61,   540,    77,
      78,    37,    60,    74,    75,   528,   675,   739,   740,   116,
      39,    62,    86,    87,    88,   306,    41,    63,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   314,   146,   147,
      43,    64,   148,   339,   149,   340,   531,   150,   341,   534,
     151,   126,   320,   127,   321,   604,   605,   606,   691,   826,
     607,   692,   608,   693,   609,   694,   610,   234,   377,   612,
     613,   614,   615,   616,   700,   617,   701,   128,   330,   640,
     641,   642,   643,   644,   645,   646,   129,   332,   651,   652,
     653,   722,    57,    71,   266,   267,   268,   390,   269,   391,
     130,   333,   660,   661,   662,   663,   664,   665,   666,   667,
     131,   326,   620,   621,   622,   705,    45,    65,   171,   172,
     173,   350,   174,   345,   175,   346,   176,   347,   177,   351,
     178,   352,   179,   356,   180,   355,   547,   181,   182,   132,
     329,   632,   633,   634,   714,   779,   780,   133,   327,    51,
      68,   624,   625,   626,   708,    53,    69,   235,   236,   237,
     238,   239,   240,   241,   376,   242,   380,   243,   379,   244,
     245,   381,   246,   134,   328,   628,   629,   630,   711,    55,
      70,   254,   255,   256,   257,   258,   385,   259,   260,   261,
     262,   184,   348,   677,   678,   679,   741,    47,    66,   196,
     197,   198,   361,   185,   349,   200,   362,   554,   186,   357,
     681,   682,   683,   744,    49,    67,   211,   212,   213,   135,
     317,   136,   318,   137,   319,   217,   372,   218,   366,   219,
     367,   220,   369,   221,   368,   222,   371,   223,   370,   224,
     365,   190,   358,   685,   747,   138,   331,   648,   649,   719,
     796,   797,   798,   799,   800,   837,   139,   140,   335,   670,
     671,   672,   733,   673,   734,   141,   336,    59,    72,   285,
     286,   287,   288,   395,   289,   396,   290,   291,   398,   292,
     293,   294,   401,   576,   295,   402,   296,   297,   298,   299,
     406,   583,   300,   407,    89,   308,    90,   309,    91,   310,
      92,   307,   588,   589,   590,   687,   848,   849,   853,   862,
     863,   864,   865,   870,   866,   868,   880,   881,   882,   889,
     890,   891,   896,   892,   893,   894
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      85,   251,    79,   166,   193,   209,   252,   233,   250,   265,
     284,   717,   775,    73,   718,   183,   195,   210,   194,   225,
     574,   199,   187,   188,   214,   215,   253,    27,    38,    28,
      26,    29,   776,   778,   189,   167,   216,   785,   312,    93,
     168,   169,   720,   313,    40,   721,   170,   107,    94,    95,
      96,    97,    98,    99,   100,   263,   264,   337,    42,   191,
     156,   192,   338,    95,    96,    97,    98,   544,   545,   546,
     101,   102,   103,   104,   105,   343,   163,   359,   106,   107,
     344,    76,   360,    44,   101,   102,   103,   885,   105,   108,
     886,   887,   888,   107,   227,   227,   247,   228,   229,   248,
     249,   263,   264,   142,   143,   109,   110,   144,   363,    46,
     145,   158,    84,   364,   226,   162,    80,   854,   111,    48,
     855,   112,   163,    50,   575,    81,    82,    83,   113,   114,
     165,    52,   115,   775,    95,    96,    97,    98,   392,   227,
      84,   228,   229,   393,    84,   230,   231,   232,    54,    96,
      97,    98,   578,   776,   778,   101,   102,   103,   785,    56,
     152,   153,   154,   227,   107,   529,   530,    96,    97,    98,
      30,    31,    32,    33,    58,   155,    84,   156,   107,   532,
     533,   157,   158,   159,   160,   161,   162,   408,   552,   553,
      84,    84,   409,   163,   164,   106,   107,   227,   337,   688,
     106,   165,   302,   686,   689,   201,   579,   580,   581,   202,
     203,   204,   205,   206,   207,   301,   208,   343,   702,   304,
     592,   303,   690,   703,   788,   593,   594,   595,   596,   597,
     598,   599,   600,   601,   602,    84,   582,   857,   305,   858,
     859,   635,   636,   637,   638,   227,   639,   702,   731,   735,
      85,   311,   704,   732,   736,   410,   411,   883,   373,    84,
     884,    84,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,   315,    84,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     408,   359,   374,    84,   835,   737,   832,   166,   316,   836,
     322,   193,   654,   655,   656,   657,   658,   659,   323,   183,
     324,   325,   209,   195,   334,   194,   187,   188,   199,    84,
     251,   392,   233,   375,   210,   252,   840,   250,   189,   167,
     342,   214,   215,   363,   168,   169,   353,   871,   844,   900,
     170,    84,   872,   216,   901,   253,   284,   822,   823,   824,
     825,   668,   669,   354,   378,   382,   383,   384,   412,   386,
     387,   388,   389,   420,   394,   397,   399,   400,   508,   509,
     510,   403,   404,   405,   413,   414,   415,   416,   417,   419,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   440,   441,
     439,   443,   444,   445,   446,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   463,
     464,   466,   467,   468,   469,   470,   471,   472,   473,   475,
     476,   477,   478,   479,   480,   481,   483,   484,   487,   488,
     491,   570,   492,   485,   490,   494,   611,   611,   493,   495,
     496,   497,   498,   603,   603,   502,   499,   503,   585,   500,
     501,   505,   506,   507,   284,   511,   515,   516,   512,   513,
     514,   517,   518,   519,   520,   521,   522,   523,   755,   535,
     524,   525,   526,   527,   538,   536,   537,    28,   541,   542,
     543,   548,   549,   550,   551,   556,   619,   623,   627,   631,
     557,   647,   650,   676,   680,   558,   559,   695,   696,   697,
     698,   699,   560,   561,   562,   706,   707,   709,   710,   713,
     712,   716,   539,   715,   563,   723,   724,   742,   684,   725,
     564,   565,   566,   567,   726,   727,   728,   729,   730,   743,
     746,   745,   418,   749,   568,   751,   748,   752,   569,   753,
     754,   577,   760,   761,   811,   812,   820,   571,   572,   814,
     815,   821,   587,   833,   839,   555,   834,   838,   845,   847,
     851,   869,   873,   875,   586,   573,   877,   879,   897,   898,
     899,   584,   902,   618,   591,   442,   447,   762,   738,   787,
     803,   802,   757,   756,   759,   758,   489,   903,   804,   805,
     764,   806,   810,   807,   763,   786,   850,   766,   765,   482,
     808,   809,   827,   828,   462,   768,   767,   486,   817,   816,
     465,   818,   819,   801,   829,   830,   474,   852,   504,   831,
     841,   842,   843,   611,   874,   674,   846,   750,   867,   813,
     603,   856,   251,   166,   876,   774,   233,   252,   878,   250,
     790,   904,   769,   895,   906,   183,   907,   789,     0,   905,
     265,     0,   187,   188,   781,     0,   777,   253,     0,   792,
     791,   782,   783,     0,   189,   167,   793,   794,     0,   193,
     168,   169,   209,   784,   770,     0,   170,     0,   795,   771,
     772,   195,     0,   194,   210,   773,   199,     0,     0,     0,
       0,   214,   215,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   216,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   774,     0,     0,     0,
     790,     0,     0,   769,     0,     0,     0,   789,     0,     0,
       0,     0,     0,     0,   861,   781,     0,   777,     0,   792,
     791,   860,   782,   783,     0,     0,   793,   794,     0,     0,
       0,     0,   861,     0,   784,   770,     0,     0,   795,   860,
     771,   772,     0,     0,     0,     0,   773
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      62,    70,    10,    65,    66,    67,    70,    69,    70,    71,
      72,     3,   714,    60,     6,    65,    66,    67,    66,    68,
      15,    66,    65,    65,    67,    67,    70,     5,     7,     7,
       0,     9,   714,   714,    65,    65,    67,   714,     3,    11,
      65,    65,     3,     8,     7,     6,    65,    51,    20,    21,
      22,    23,    24,    25,    26,    91,    92,     3,     7,    63,
      64,    65,     8,    21,    22,    23,    24,    74,    75,    76,
      42,    43,    44,    45,    46,     3,    80,     3,    50,    51,
       8,   148,     8,     7,    42,    43,    44,   127,    46,    61,
     130,   131,   132,    51,    52,    52,    53,    54,    55,    56,
      57,    91,    92,    12,    13,    77,    78,    16,     3,     7,
      19,    69,   148,     8,    27,    73,   124,     3,    90,     7,
       6,    93,    80,     7,   119,   133,   134,   135,   100,   101,
      88,     7,   104,   835,    21,    22,    23,    24,     3,    52,
     148,    54,    55,     8,   148,    58,    59,    60,     7,    22,
      23,    24,    67,   835,   835,    42,    43,    44,   835,     7,
      47,    48,    49,    52,    51,    14,    15,    22,    23,    24,
     148,   149,   150,   151,     7,    62,   148,    64,    51,    17,
      18,    68,    69,    70,    71,    72,    73,     3,    66,    67,
     148,   148,     8,    80,    81,    50,    51,    52,     3,     3,
      50,    88,     3,     8,     8,    78,   121,   122,   123,    82,
      83,    84,    85,    86,    87,     6,    89,     3,     3,     8,
      27,     4,     8,     8,    79,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,   148,   151,   126,     3,   128,
     129,    82,    83,    84,    85,    52,    87,     3,     3,     3,
     312,     4,     8,     8,     8,   302,   303,     3,     8,   148,
       6,   148,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,     4,   148,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
       3,     3,     3,   148,     3,     8,     8,   359,     4,     8,
       4,   363,    94,    95,    96,    97,    98,    99,     4,   359,
       4,     4,   374,   363,     4,   363,   359,   359,   363,   148,
     389,     3,   384,     8,   374,   389,     8,   389,   359,   359,
       4,   374,   374,     3,   359,   359,     4,     3,     8,     3,
     359,   148,     8,   374,     8,   389,   408,    28,    29,    30,
      31,   102,   103,     4,     4,     4,     8,     3,   148,     4,
       4,     8,     3,   151,     4,     4,     4,     4,   415,   416,
     417,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     151,     4,     4,     4,     4,     4,   149,   149,   149,   149,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     149,     4,     4,     4,   151,     4,     4,     4,     4,     4,
       4,     4,     4,   149,   151,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   149,     4,     4,     4,   151,     4,   151,     4,     4,
       4,   488,     4,   151,   151,     4,   515,   516,   149,   149,
     149,     4,     4,   515,   516,     4,   151,     4,   505,   151,
     151,     4,     7,     7,   526,     7,     7,     7,   148,   148,
     148,     5,     5,     5,     5,     5,     5,     5,   149,   148,
       7,     7,     7,     5,     5,   148,   148,     7,   148,   148,
     148,   148,     5,     7,   148,   148,     7,     7,     7,     7,
     148,     7,     7,     7,     7,   148,   148,     4,     4,     4,
       4,     4,   148,   148,   148,     6,     3,     6,     3,     3,
       6,     3,   452,     6,   148,     6,     3,     6,    89,     4,
     148,   148,   148,   148,     4,     4,     4,     4,     4,     3,
       3,     6,   312,     4,   148,     4,     8,     4,   148,     4,
       4,   120,     4,     4,     4,     4,     4,   148,   148,     6,
       3,     5,   125,     8,     3,   466,     8,     8,     8,     7,
       4,     4,     4,     4,   506,   148,     5,     7,     4,     4,
       4,   148,     4,   516,   511,   337,   343,   702,   148,   717,
     724,   722,   149,   151,   149,   151,   392,   151,   149,   149,
     707,   149,   731,   149,   705,   716,   835,   710,   708,   384,
     149,   149,   148,   148,   359,   713,   711,   389,   743,   741,
     363,   744,   746,   720,   148,   148,   374,   839,   408,   148,
     148,   148,   148,   702,   149,   526,   148,   688,   854,   735,
     702,   148,   711,   705,   871,   714,   708,   711,   148,   711,
     719,   149,   714,   883,   900,   705,   148,   719,    -1,   149,
     722,    -1,   705,   705,   714,    -1,   714,   711,    -1,   719,
     719,   714,   714,    -1,   705,   705,   719,   719,    -1,   741,
     705,   705,   744,   714,   714,    -1,   705,    -1,   719,   714,
     714,   741,    -1,   741,   744,   714,   741,    -1,    -1,    -1,
      -1,   744,   744,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   744,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   835,    -1,    -1,    -1,
     839,    -1,    -1,   835,    -1,    -1,    -1,   839,    -1,    -1,
      -1,    -1,    -1,    -1,   853,   835,    -1,   835,    -1,   839,
     839,   853,   835,   835,    -1,    -1,   839,   839,    -1,    -1,
      -1,    -1,   871,    -1,   835,   835,    -1,    -1,   839,   871,
     835,   835,    -1,    -1,    -1,    -1,   835
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     0,     5,     7,     9,
     148,   149,   150,   151,   166,   167,   168,   173,     7,   182,
       7,   188,     7,   202,     7,   278,     7,   359,     7,   376,
       7,   311,     7,   317,     7,   341,     7,   254,     7,   429,
     174,   169,   183,   189,   203,   279,   360,   377,   312,   318,
     342,   255,   430,   166,   175,   176,   148,   171,   172,    10,
     124,   133,   134,   135,   148,   181,   184,   185,   186,   456,
     458,   460,   462,    11,    20,    21,    22,    23,    24,    25,
      26,    42,    43,    44,    45,    46,    50,    51,    61,    77,
      78,    90,    93,   100,   101,   104,   181,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   213,   215,   239,   248,
     262,   272,   301,   309,   335,   381,   383,   385,   407,   418,
     419,   427,    12,    13,    16,    19,   200,   201,   204,   206,
     209,   212,    47,    48,    49,    62,    64,    68,    69,    70,
      71,    72,    73,    80,    81,    88,   181,   192,   193,   194,
     197,   280,   281,   282,   284,   286,   288,   290,   292,   294,
     296,   299,   300,   335,   353,   365,   370,   381,   383,   385,
     403,    63,    65,   181,   294,   335,   361,   362,   363,   365,
     367,    78,    82,    83,    84,    85,    86,    87,    89,   181,
     335,   378,   379,   380,   381,   383,   385,   387,   389,   391,
     393,   395,   397,   399,   401,   309,    27,    52,    54,    55,
      58,    59,    60,   181,   229,   319,   320,   321,   322,   323,
     324,   325,   327,   329,   331,   332,   334,    53,    56,    57,
     181,   229,   323,   329,   343,   344,   345,   346,   347,   349,
     350,   351,   352,    91,    92,   181,   256,   257,   258,   260,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   181,   431,   432,   433,   434,   436,
     438,   439,   441,   442,   443,   446,   448,   449,   450,   451,
     454,     6,     3,     4,     8,     3,   187,   463,   457,   459,
     461,     4,     3,     8,   199,     4,     4,   382,   384,   386,
     214,   216,     4,     4,     4,     4,   273,   310,   336,   302,
     240,   408,   249,   263,     4,   420,   428,     3,     8,   205,
     207,   210,     4,     3,     8,   285,   287,   289,   354,   366,
     283,   291,   293,     4,     4,   297,   295,   371,   404,     3,
       8,   364,   368,     3,     8,   402,   390,   392,   396,   394,
     400,   398,   388,     8,     3,     8,   326,   230,     4,   330,
     328,   333,     4,     8,     3,   348,     4,     4,     8,     3,
     259,   261,     3,     8,     4,   435,   437,     4,   440,     4,
       4,   444,   447,     4,     4,     4,   452,   455,     3,     8,
     166,   166,   148,     4,     4,     4,     4,     4,   185,     4,
     151,   151,     4,     4,     4,     4,     4,   149,   149,   149,
     149,     4,     4,     4,     4,     4,     4,     4,     4,   149,
       4,     4,   191,     4,     4,     4,   151,   201,     4,     4,
       4,     4,     4,     4,     4,     4,   149,   151,     4,     4,
       4,     4,   281,     4,     4,   362,     4,     4,     4,     4,
       4,     4,     4,     4,   380,     4,     4,   149,     4,     4,
       4,   151,   321,     4,   151,   151,   345,     4,     4,   257,
     151,     4,     4,   149,     4,   149,   149,     4,     4,   151,
     151,   151,     4,     4,   432,     4,     7,     7,   166,   166,
     166,     7,   148,   148,   148,     7,     7,     5,     5,     5,
       5,     5,     5,     5,     7,     7,     7,     5,   177,    14,
      15,   208,    17,    18,   211,   148,   148,   148,     5,   168,
     170,   148,   148,   148,    74,    75,    76,   298,   148,     5,
       7,   148,    66,    67,   369,   177,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     166,   148,   148,   148,    15,   119,   445,   120,    67,   121,
     122,   123,   151,   453,   148,   166,   190,   125,   464,   465,
     466,   200,    27,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,   181,   217,   218,   219,   222,   224,   226,
     228,   229,   231,   232,   233,   234,   235,   237,   217,     7,
     274,   275,   276,     7,   313,   314,   315,     7,   337,   338,
     339,     7,   303,   304,   305,    82,    83,    84,    85,    87,
     241,   242,   243,   244,   245,   246,   247,     7,   409,   410,
       7,   250,   251,   252,    94,    95,    96,    97,    98,    99,
     264,   265,   266,   267,   268,   269,   270,   271,   102,   103,
     421,   422,   423,   425,   431,   178,     7,   355,   356,   357,
       7,   372,   373,   374,    89,   405,     8,   467,     3,     8,
       8,   220,   223,   225,   227,     4,     4,     4,     4,     4,
     236,   238,     3,     8,     8,   277,     6,     3,   316,     6,
       3,   340,     6,     3,   306,     6,     3,     3,     6,   411,
       3,     6,   253,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   424,   426,     3,     8,     8,   148,   179,
     180,   358,     6,     3,   375,     6,     3,   406,     8,     4,
     465,     4,     4,     4,     4,   149,   151,   149,   151,   149,
       4,     4,   218,   280,   276,   319,   315,   343,   339,   181,
     192,   193,   194,   197,   229,   272,   290,   294,   296,   307,
     308,   335,   381,   383,   385,   403,   305,   242,    79,   181,
     229,   309,   335,   381,   383,   385,   412,   413,   414,   415,
     416,   410,   256,   252,   149,   149,   149,   149,   149,   149,
     265,     4,     4,   422,     6,     3,   361,   357,   378,   374,
       4,     5,    28,    29,    30,    31,   221,   148,   148,   148,
     148,   148,     8,     8,     8,     3,     8,   417,     8,     3,
       8,   148,   148,   148,     8,     8,   148,     7,   468,   469,
     308,     4,   414,   470,     3,     6,   148,   126,   128,   129,
     181,   229,   471,   472,   473,   474,   476,   469,   477,     4,
     475,     3,     8,     4,   149,     4,   472,     5,   148,     7,
     478,   479,   480,     3,     6,   127,   130,   131,   132,   481,
     482,   483,   485,   486,   487,   479,   484,     4,     4,     4,
       3,     8,     4,   151,   149,   149,   482,   148
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
     281,   281,   281,   281,   281,   281,   281,   283,   282,   285,
     284,   287,   286,   289,   288,   291,   290,   293,   292,   295,
     294,   297,   296,   298,   298,   298,   299,   300,   302,   301,
     303,   303,   304,   304,   306,   305,   307,   307,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   310,   309,   312,   311,   313,   313,   314,
     314,   316,   315,   318,   317,   319,   319,   320,   320,   321,
     321,   321,   321,   321,   321,   321,   321,   322,   323,   324,
     326,   325,   328,   327,   330,   329,   331,   333,   332,   334,
     336,   335,   337,   337,   338,   338,   340,   339,   342,   341,
     343,   343,   344,   344,   345,   345,   345,   345,   345,   345,
     345,   346,   348,   347,   349,   350,   351,   352,   354,   353,
     355,   355,   356,   356,   358,   357,   360,   359,   361,   361,
     362,   362,   362,   362,   362,   362,   364,   363,   366,   365,
     368,   367,   369,   369,   371,   370,   372,   372,   373,   373,
     375,   374,   377,   376,   378,   378,   379,   379,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   382,   381,   384,   383,   386,   385,   388,   387,   390,
     389,   392,   391,   394,   393,   396,   395,   398,   397,   400,
     399,   402,   401,   404,   403,   406,   405,   408,   407,   409,
     409,   411,   410,   412,   412,   413,   413,   414,   414,   414,
     414,   414,   414,   414,   414,   415,   417,   416,   418,   420,
     419,   421,   421,   422,   422,   424,   423,   426,   425,   428,
     427,   430,   429,   431,   431,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     433,   435,   434,   437,   436,   438,   440,   439,   441,   442,
     444,   443,   445,   445,   447,   446,   448,   449,   450,   452,
     451,   453,   453,   453,   453,   453,   455,   454,   457,   456,
     459,   458,   461,   460,   463,   462,   464,   464,   465,   467,
     466,   468,   468,   470,   469,   471,   471,   472,   472,   472,
     472,   472,   473,   475,   474,   477,   476,   478,   478,   480,
     479,   481,   481,   482,   482,   482,   482,   484,   483,   485,
     486,   487
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
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
  "$@69", "known_clients", "$@70", "known_clients_value", "reservations",
  "$@71", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@72", "sub_reservation", "$@73", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@74", "server_hostname", "$@75", "boot_file_name", "$@76",
  "ip_address", "$@77", "duid", "$@78", "hw_address", "$@79",
  "client_id_value", "$@80", "circuit_id_value", "$@81", "flex_id_value",
  "$@82", "hostname", "$@83", "reservation_client_classes", "$@84",
  "relay", "$@85", "relay_map", "$@86", "client_classes", "$@87",
  "client_classes_list", "client_class_entry", "$@88",
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
       0,   236,   236,   236,   237,   237,   238,   238,   239,   239,
     240,   240,   241,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   247,   255,   256,   257,   258,
     259,   260,   261,   264,   269,   269,   280,   283,   284,   287,
     291,   298,   298,   305,   306,   309,   313,   320,   320,   327,
     328,   331,   335,   346,   356,   356,   372,   373,   377,   378,
     379,   380,   381,   382,   385,   385,   400,   400,   409,   410,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   441,   446,   451,   456,   461,   466,
     472,   472,   483,   484,   487,   488,   489,   490,   493,   493,
     502,   502,   512,   512,   519,   520,   523,   523,   530,   532,
     536,   542,   542,   554,   554,   566,   567,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     585,   585,   592,   593,   594,   595,   598,   598,   606,   606,
     614,   614,   622,   627,   627,   635,   640,   645,   650,   655,
     655,   663,   663,   672,   672,   682,   683,   686,   687,   688,
     689,   690,   693,   698,   703,   708,   713,   718,   718,   728,
     729,   732,   733,   736,   736,   746,   746,   756,   757,   758,
     761,   762,   765,   765,   773,   773,   781,   781,   792,   793,
     796,   797,   798,   799,   800,   801,   804,   809,   814,   819,
     824,   829,   837,   837,   850,   851,   854,   855,   862,   862,
     888,   888,   899,   900,   904,   905,   906,   907,   908,   909,
     910,   911,   912,   913,   914,   915,   916,   917,   918,   919,
     920,   921,   922,   923,   924,   925,   926,   929,   929,   937,
     937,   945,   945,   953,   953,   961,   961,   969,   969,   977,
     977,   985,   985,   992,   993,   994,   997,  1002,  1009,  1009,
    1020,  1021,  1025,  1026,  1029,  1029,  1037,  1038,  1041,  1042,
    1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,
    1053,  1054,  1055,  1062,  1062,  1075,  1075,  1084,  1085,  1088,
    1089,  1094,  1094,  1109,  1109,  1123,  1124,  1127,  1128,  1131,
    1132,  1133,  1134,  1135,  1136,  1137,  1138,  1141,  1143,  1148,
    1150,  1150,  1158,  1158,  1166,  1166,  1174,  1176,  1176,  1184,
    1193,  1193,  1205,  1206,  1211,  1212,  1217,  1217,  1229,  1229,
    1241,  1242,  1247,  1248,  1253,  1254,  1255,  1256,  1257,  1258,
    1259,  1262,  1264,  1264,  1272,  1274,  1276,  1281,  1289,  1289,
    1301,  1302,  1305,  1306,  1309,  1309,  1319,  1319,  1329,  1330,
    1333,  1334,  1335,  1336,  1337,  1338,  1341,  1341,  1349,  1349,
    1356,  1356,  1364,  1365,  1371,  1371,  1381,  1382,  1385,  1386,
    1389,  1389,  1398,  1398,  1407,  1408,  1411,  1412,  1416,  1417,
    1418,  1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,  1427,
    1428,  1431,  1431,  1439,  1439,  1447,  1447,  1455,  1455,  1463,
    1463,  1471,  1471,  1479,  1479,  1487,  1487,  1495,  1495,  1503,
    1503,  1511,  1511,  1524,  1524,  1534,  1534,  1545,  1545,  1555,
    1556,  1559,  1559,  1569,  1570,  1573,  1574,  1577,  1578,  1579,
    1580,  1581,  1582,  1583,  1584,  1587,  1589,  1589,  1601,  1608,
    1608,  1618,  1619,  1622,  1623,  1626,  1626,  1634,  1634,  1644,
    1644,  1656,  1656,  1666,  1667,  1670,  1671,  1672,  1673,  1674,
    1675,  1676,  1677,  1678,  1679,  1680,  1681,  1682,  1683,  1684,
    1687,  1692,  1692,  1700,  1700,  1708,  1713,  1713,  1721,  1726,
    1731,  1731,  1739,  1740,  1743,  1743,  1751,  1756,  1761,  1766,
    1766,  1774,  1777,  1780,  1783,  1786,  1792,  1792,  1802,  1802,
    1809,  1809,  1816,  1816,  1828,  1828,  1841,  1842,  1846,  1850,
    1850,  1862,  1863,  1867,  1867,  1875,  1876,  1879,  1880,  1881,
    1882,  1883,  1886,  1891,  1891,  1899,  1899,  1909,  1910,  1913,
    1913,  1921,  1922,  1925,  1926,  1927,  1928,  1931,  1931,  1939,
    1944,  1949
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
#line 4425 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1954 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
