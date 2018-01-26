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
      case 167: // value
      case 171: // map_value
      case 209: // socket_type
      case 212: // outbound_interface_value
      case 222: // db_type
      case 299: // hr_mode
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
      case 167: // value
      case 171: // map_value
      case 209: // socket_type
      case 212: // outbound_interface_value
      case 222: // db_type
      case 299: // hr_mode
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

      case 167: // value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 394 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 171: // map_value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 401 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 209: // socket_type

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 408 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 212: // outbound_interface_value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 415 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 222: // db_type

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 422 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 299: // hr_mode

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
      case 167: // value
      case 171: // map_value
      case 209: // socket_type
      case 212: // outbound_interface_value
      case 222: // db_type
      case 299: // hr_mode
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
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 762 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 768 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 256 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 774 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 257 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 780 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 258 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 786 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 259 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 792 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 798 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 261 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 264 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 824 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 274 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 834 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 280 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 840 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 287 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 291 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 298 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 309 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 885 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 894 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 320 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 902 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 911 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 331 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 920 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 335 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 346 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 356 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 361 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 385 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 392 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 987 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 400 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 404 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1006 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 458 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 463 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1051 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 468 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 474 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 479 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1100 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 519 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1137 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 524 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 525 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1149 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1157 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 530 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1166 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1174 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 541 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 547 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1202 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 564 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1235 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 590 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 597 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1258 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 598 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 599 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 600 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 611 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1302 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 619 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 621 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 627 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1339 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 634 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 162:
#line 640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 645 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1384 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 655 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1419 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1429 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 677 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1440 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 682 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 698 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1458 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1467 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 181:
#line 708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1476 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 182:
#line 713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1485 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1494 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1514 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1524 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 191:
#line 745 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1534 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 192:
#line 751 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1544 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 193:
#line 755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1554 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 770 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1562 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 778 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1580 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1589 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1619 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 814 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 819 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1637 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 216:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1646 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 217:
#line 829 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1655 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 218:
#line 834 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1664 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 219:
#line 842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1684 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 225:
#line 867 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 226:
#line 871 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 1720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 227:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1730 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 228:
#line 897 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1748 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 937 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 943 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 945 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 959 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 961 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1820 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 264:
#line 969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 265:
#line 975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1848 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1856 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 268:
#line 985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 269:
#line 991 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1874 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 270:
#line 993 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1883 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 271:
#line 998 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 272:
#line 999 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1000 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1901 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1910 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 275:
#line 1008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1919 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 276:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1930 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 277:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1035 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 283:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1075 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1083 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1994 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2004 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1106 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2016 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1117 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2026 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2038 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1160 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2065 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2083 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2101 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 339:
#line 1186 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2119 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2128 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1203 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2139 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2148 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1227 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2158 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1231 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2167 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1239 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2177 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1243 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 366:
#line 1276 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 367:
#line 1278 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1288 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1293 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2222 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1301 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1306 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2242 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1321 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2252 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1325 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2262 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1335 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1363 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2335 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1388 "dhcp4_parser.yy" // lalr1.cc:859
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
#line 2372 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1416 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2383 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1421 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2392 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1434 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2411 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1447 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2430 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2448 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1488 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1494 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1502 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1512 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1520 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1536 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1550 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2630 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1571 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2641 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1576 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2650 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2668 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2679 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2688 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1606 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1610 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1640 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2735 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1662 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1678 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1686 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1696 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2813 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1712 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2833 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2842 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1746 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2850 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1748 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2860 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1754 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1756 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2878 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1762 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2887 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1767 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2905 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1775 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1780 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1785 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1793 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2946 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2952 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1797 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2970 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1805 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2979 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1810 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1815 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3005 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3014 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3022 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1831 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1834 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3038 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3046 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1840 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3055 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1846 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3063 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1848 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3073 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1856 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3081 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1858 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3090 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1863 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1865 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3115 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3124 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1882 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1887 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3144 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1892 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1896 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3162 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1912 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3182 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3192 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3200 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1950 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3209 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1955 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3217 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1957 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3227 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3247 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 575:
#line 1981 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3265 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 582:
#line 1995 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 583:
#line 1997 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3283 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2003 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3292 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2008 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3301 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2013 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3310 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3314 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -719;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     296,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,    32,    22,    33,    81,    92,   101,
     138,   142,   162,   177,   193,   209,   246,   258,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,    22,  -110,     8,    59,    53,   155,
     -12,    11,    10,   349,   190,    17,   314,   -57,  -719,    84,
     126,   156,   159,   263,  -719,  -719,  -719,  -719,  -719,   272,
    -719,    46,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   274,
     283,  -719,  -719,  -719,  -719,  -719,   293,   294,   318,   326,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
     328,  -719,  -719,  -719,   108,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,   330,  -719,   118,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,   331,   332,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,   122,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,   129,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,   260,   313,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   288,  -719,
    -719,   341,  -719,  -719,  -719,   344,  -719,  -719,   348,   346,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,   355,   356,  -719,  -719,  -719,  -719,   354,
     360,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,   130,  -719,  -719,  -719,   362,  -719,  -719,
     363,  -719,   364,   366,  -719,  -719,   368,   370,   376,  -719,
    -719,  -719,  -719,  -719,   210,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,   228,  -719,  -719,  -719,    22,    22,  -719,   204,   380,
     383,   389,   390,   391,  -719,     8,  -719,   392,   213,   247,
     393,   396,   398,   402,   406,   262,   266,   267,   295,   408,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   306,
     450,   452,    59,  -719,   453,   454,   455,   309,    53,  -719,
     457,   460,   461,   462,   463,   464,   465,   323,   324,   470,
     472,   475,   476,   155,  -719,   477,   479,   -12,  -719,   480,
     482,   483,   484,   485,   488,   489,  -719,    11,  -719,   490,
     491,   347,   494,   495,   496,   350,  -719,   349,   500,   357,
     358,  -719,   190,   501,   502,   -31,  -719,   359,   503,   507,
     365,   508,   367,   369,   511,   513,   371,   372,   373,   515,
     516,   314,  -719,   517,   -57,  -719,  -719,  -719,   521,   519,
     520,    22,    22,    22,  -719,   522,  -719,  -719,   384,   385,
     386,   528,   529,  -719,  -719,  -719,  -719,   523,   532,   533,
     534,   535,   395,   536,   539,   540,   541,  -719,   542,   543,
    -719,   546,   195,    60,  -719,  -719,   399,   404,   405,   549,
     407,   409,   410,  -719,  -719,   166,   411,   551,   553,  -719,
     413,   546,  -719,   414,   415,   416,   417,   418,   419,   420,
    -719,   421,   422,  -719,   423,   424,   425,  -719,  -719,   426,
    -719,  -719,  -719,   427,    22,  -719,  -719,   428,   429,  -719,
     430,  -719,  -719,    31,   466,  -719,  -719,  -719,    -7,   431,
    -719,   575,  -719,    22,    59,   -57,  -719,  -719,  -719,    53,
    -719,  -719,  -719,   153,   153,   574,   576,   578,   579,  -719,
    -719,  -719,   200,   580,   581,   167,    63,   314,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   582,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   583,   459,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,   584,  -719,   229,   248,   264,  -719,  -719,  -719,  -719,
     588,   589,   590,   591,   592,  -719,  -719,  -719,   285,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,   291,  -719,   593,   537,  -719,  -719,   594,   595,
    -719,  -719,   596,   598,  -719,  -719,   597,   601,  -719,  -719,
    -719,  -719,  -719,  -719,    83,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,    94,  -719,  -719,   599,   603,  -719,   604,   605,
     606,   607,   608,   609,   292,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,   301,  -719,  -719,
    -719,   302,   434,  -719,   610,   611,  -719,  -719,   612,   614,
    -719,  -719,   613,  -719,   116,  -719,  -719,  -719,  -719,   615,
     616,   618,   619,   458,   473,   478,   474,   481,   622,   624,
     153,  -719,  -719,   155,  -719,   574,   349,  -719,   576,   190,
    -719,   578,   206,  -719,   579,   200,  -719,   131,   580,  -719,
      17,  -719,   581,   486,   487,   492,   493,   497,   498,   167,
    -719,   625,   627,    63,  -719,  -719,  -719,   626,   630,   -12,
    -719,   582,    11,  -719,   583,   633,  -719,    87,   584,  -719,
     297,   467,   504,   505,  -719,  -719,  -719,  -719,  -719,   506,
     510,  -719,   303,  -719,   631,  -719,   632,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   304,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   635,
     641,  -719,  -719,  -719,  -719,   305,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,   512,   514,  -719,  -719,   524,   312,
    -719,   637,  -719,   527,  -719,   634,  -719,  -719,  -719,  -719,
    -719,   315,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
     206,  -719,   644,  -719,   131,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,   645,   531,   646,    87,  -719,  -719,   530,  -719,
     629,  -719,   544,  -719,  -719,   648,  -719,  -719,   140,  -719,
     160,   648,  -719,  -719,   647,   652,   655,   316,  -719,  -719,
    -719,  -719,  -719,  -719,   657,   538,   545,   559,   160,  -719,
     547,  -719,  -719,  -719,  -719,  -719
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   115,     9,   227,    11,   380,    13,
     404,    15,   305,    17,   313,    19,   350,    21,   192,    23,
     490,    25,   547,    27,    45,    39,     0,     0,     0,     0,
       0,   406,     0,   315,   352,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   545,   539,   541,   543,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   104,     0,
       0,   425,   427,   429,   128,   130,     0,     0,     0,     0,
     219,   303,   342,   276,   392,   394,   170,   451,   184,   203,
       0,   475,   488,    97,     0,    70,    72,    73,    74,    75,
      90,    91,    78,    79,    80,    81,    85,    86,    76,    77,
      83,    84,    95,    96,    92,    93,    94,    82,    87,    88,
      89,   117,   119,   123,     0,   114,     0,   106,   108,   109,
     110,   111,   112,   113,   257,   259,   261,   372,   255,   263,
     265,     0,     0,   269,   267,   396,   447,   254,   231,   232,
     233,   245,     0,   229,   236,   249,   250,   251,   237,   238,
     241,   243,   239,   240,   234,   235,   252,   253,   242,   246,
     247,   248,   244,   390,   445,   389,   385,     0,   382,   384,
     387,   388,   386,   433,   435,   439,   437,   443,   441,   431,
     424,   418,   422,   423,     0,   407,   408,   419,   420,   421,
     415,   410,   416,   412,   413,   414,   417,   411,     0,   332,
     160,     0,   336,   334,   339,     0,   328,   329,     0,   316,
     317,   319,   331,   320,   321,   322,   338,   323,   324,   325,
     326,   327,   366,     0,     0,   364,   365,   368,   369,     0,
     353,   354,   356,   357,   358,   359,   360,   361,   362,   363,
     199,   201,   196,     0,   194,   197,   198,     0,   512,   514,
       0,   517,     0,     0,   521,   525,     0,     0,     0,   530,
     537,   510,   508,   509,     0,   492,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     552,     0,   549,   551,    44,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    55,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   228,     0,     0,     0,   381,     0,
       0,     0,     0,     0,     0,     0,   405,     0,   306,     0,
       0,     0,     0,     0,     0,     0,   314,     0,     0,     0,
       0,   351,     0,     0,     0,     0,   193,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   491,     0,     0,   548,    48,    41,     0,     0,
       0,     0,     0,     0,    59,     0,   102,   103,     0,     0,
       0,     0,     0,    98,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   474,     0,     0,
      71,     0,     0,     0,   127,   107,     0,     0,     0,     0,
       0,     0,     0,   274,   275,     0,     0,     0,     0,   230,
       0,     0,   383,     0,     0,     0,     0,     0,     0,     0,
     409,     0,     0,   330,     0,     0,     0,   341,   318,     0,
     370,   371,   355,     0,     0,   195,   511,     0,     0,   516,
       0,   519,   520,     0,     0,   527,   528,   529,     0,     0,
     493,     0,   550,     0,     0,     0,   540,   542,   544,     0,
     426,   428,   430,     0,     0,   221,   307,   344,   278,    38,
     393,   395,     0,     0,   186,     0,     0,     0,    49,   118,
     121,   122,   120,   125,   126,   124,   258,   260,   262,   374,
     256,   264,   266,   271,   272,   273,   270,   268,   398,     0,
     391,   446,   434,   436,   440,   438,   444,   442,   432,   333,
     161,   337,   335,   340,   367,   200,   202,   513,   515,   518,
     523,   524,   522,   526,   532,   533,   534,   535,   536,   531,
     538,     0,    42,     0,     0,     0,   147,   153,   155,   157,
       0,     0,     0,     0,     0,   166,   168,   146,     0,   132,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,     0,   225,     0,   222,   223,   311,     0,   308,
     309,   348,     0,   345,   346,   282,     0,   279,   280,   179,
     180,   181,   182,   183,     0,   172,   174,   175,   176,   177,
     178,   455,     0,   453,   190,     0,   187,   188,     0,     0,
       0,     0,     0,     0,     0,   205,   207,   208,   209,   210,
     211,   212,   484,   486,   483,   481,   482,     0,   477,   479,
     480,     0,    51,   378,     0,   375,   376,   402,     0,   399,
     400,   449,     0,   556,     0,   554,    67,   546,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   129,   131,     0,   220,     0,   315,   304,     0,   352,
     343,     0,     0,   277,     0,     0,   171,   457,     0,   452,
       0,   185,     0,     0,     0,     0,     0,     0,     0,     0,
     204,     0,     0,     0,   476,   489,    53,     0,    52,     0,
     373,     0,   406,   397,     0,     0,   448,     0,     0,   553,
       0,     0,     0,     0,   159,   162,   163,   164,   165,     0,
       0,   133,     0,   224,     0,   310,     0,   347,   302,   299,
     289,   290,   292,   286,   287,   288,   298,   297,     0,   284,
     291,   300,   301,   293,   294,   295,   296,   281,   173,   472,
     470,   471,   463,   464,   468,   469,   465,   466,   467,     0,
     458,   459,   461,   462,   454,     0,   189,   213,   214,   215,
     216,   217,   218,   206,     0,     0,   478,    50,     0,     0,
     377,     0,   401,     0,   570,     0,   568,   566,   560,   564,
     565,     0,   558,   562,   563,   561,   555,   149,   150,   151,
     152,   148,   154,   156,   158,   167,   169,   226,   312,   349,
       0,   283,     0,   456,     0,   191,   485,   487,    54,   379,
     403,   450,     0,     0,     0,     0,   557,   285,     0,   460,
       0,   567,     0,   559,   473,     0,   569,   574,     0,   572,
       0,     0,   571,   582,     0,     0,     0,     0,   576,   578,
     579,   580,   581,   573,     0,     0,     0,     0,     0,   575,
       0,   584,   585,   586,   577,   583
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,   -51,  -719,   136,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,   172,  -719,  -719,  -719,
     -66,  -719,  -719,  -719,   333,  -719,  -719,  -719,  -719,   149,
     329,   -43,   -28,    -1,  -719,  -719,     5,  -719,  -719,   161,
     334,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,   121,   -32,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   -73,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,   -33,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,   -35,  -719,  -719,  -719,   -30,   321,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,   -29,  -719,  -719,  -719,  -719,  -719,
    -719,  -718,  -719,  -719,  -719,   -11,  -719,  -719,  -719,    -6,
     374,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -714,
    -719,  -719,  -719,  -712,  -719,  -706,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,   -15,  -719,  -719,  -149,   -61,  -719,
    -719,  -719,  -719,  -719,     4,  -719,  -719,  -719,     9,  -719,
     343,  -719,   -68,  -719,  -719,  -719,  -719,  -719,   -62,  -719,
    -719,  -719,  -719,  -719,   -14,  -719,  -719,  -719,     7,  -719,
    -719,  -719,     1,  -719,   340,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,   -18,  -719,  -719,  -719,
     -13,   375,  -719,  -719,   -54,  -719,   -26,  -719,  -719,  -719,
    -719,  -719,   -20,  -719,  -719,  -719,    -9,  -719,   378,   -46,
    -719,    -8,  -719,     2,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   -50,
    -719,  -705,  -719,  -719,  -719,  -719,  -719,  -719,    12,  -719,
    -719,  -719,  -125,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
      -2,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,   208,
     335,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,  -719,
    -719,  -719,  -719,  -719,   232,   336,  -719,  -719,  -719,   -10,
    -719,  -719,  -126,  -719,  -719,  -719,  -719,  -719,  -719,  -140,
    -719,  -719,  -156,  -719,  -719,  -719,  -719,  -719
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   550,
      82,    83,    39,    64,    79,    80,   559,   702,   767,   768,
     123,    41,    66,    91,    92,    93,   329,    43,    67,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   337,   156,
     157,    45,    68,   158,   364,   159,   365,   562,   160,   366,
     565,   161,   133,   343,   134,   344,   628,   629,   630,   719,
     871,   631,   720,   632,   721,   633,   722,   634,   247,   400,
     636,   637,   638,   639,   640,   728,   641,   729,   135,   355,
     664,   665,   666,   667,   668,   669,   670,   136,   357,   675,
     676,   677,   750,    59,    75,   283,   284,   285,   413,   286,
     414,   137,   358,   684,   685,   686,   687,   688,   689,   690,
     691,   138,   349,   644,   645,   646,   733,    47,    69,   182,
     183,   184,   374,   185,   370,   186,   371,   187,   372,   188,
     375,   189,   376,   190,   380,   191,   379,   576,   192,   193,
     139,   352,   656,   657,   658,   742,   808,   809,   140,   350,
      53,    72,   648,   649,   650,   736,    55,    73,   248,   249,
     250,   251,   252,   253,   254,   399,   255,   403,   256,   402,
     257,   258,   404,   259,   141,   351,   652,   653,   654,   739,
      57,    74,   269,   270,   271,   272,   273,   408,   274,   275,
     276,   277,   195,   373,   704,   705,   706,   769,    49,    70,
     207,   208,   209,   385,   142,   353,   143,   354,   198,   381,
     708,   709,   710,   772,    51,    71,   224,   225,   226,   144,
     340,   145,   341,   146,   342,   230,   395,   231,   389,   232,
     390,   233,   392,   234,   391,   235,   394,   236,   393,   212,
     386,   202,   382,   712,   775,   147,   356,   672,   673,   747,
     829,   830,   831,   832,   833,   882,   148,   149,   360,   697,
     698,   699,   761,   700,   762,   150,   361,    61,    76,   304,
     305,   306,   307,   418,   308,   419,   309,   310,   421,   311,
     312,   313,   424,   602,   314,   425,   315,   316,   317,   318,
     429,   609,   319,   430,    94,   331,    95,   332,    96,   333,
      97,   330,    63,    77,   321,   322,   323,   433,   714,   715,
     777,   861,   862,   863,   864,   894,   865,   892,   908,   909,
     910,   917,   918,   919,   924,   920,   921,   922
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   266,   155,   177,   205,   220,   267,   246,   265,   282,
     301,   238,   268,    78,   162,   196,   210,   222,    84,   260,
     278,   237,   302,   199,   804,   227,   178,    29,   805,    30,
     806,    31,    28,   101,   102,   103,   807,   816,    81,   112,
      40,   179,   163,   197,   211,   223,   600,   261,   279,   335,
     303,   203,   114,   115,   336,   194,   206,   221,   280,   281,
     111,   200,   112,   228,   204,   151,   152,   320,   180,   153,
      98,   201,   154,   229,   181,   114,   115,   563,   564,    99,
     100,   101,   102,   103,   104,   105,   745,   204,    42,   746,
     324,   213,   214,   215,   216,   217,   218,   748,   219,    44,
     749,   106,   107,   108,   109,   110,   280,   281,    46,   111,
     112,   362,   604,   605,   606,   607,   363,   114,   115,   778,
     113,   368,   779,   114,   115,   383,   369,   114,   115,   325,
     384,    85,   387,   415,   116,   117,    89,   388,   416,   240,
      86,    87,    88,   911,   608,    48,   912,   118,   601,    50,
     119,   114,   115,   101,   102,   103,    89,   120,   121,    89,
     326,   122,   804,   692,   693,    89,   805,   327,   806,    52,
      32,    33,    34,    35,   807,   816,   100,   101,   102,   103,
     616,   111,   112,   240,    54,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   114,   115,   106,   107,   108,
      56,    89,   164,   165,   166,   240,   112,    89,   819,   560,
     561,    89,   854,   431,   855,   856,    58,   167,   432,   114,
     115,   168,   169,   170,   171,   172,   173,   100,   101,   102,
     103,   434,   362,   174,   175,    89,   435,   716,   573,   574,
     575,   176,   240,   262,   241,   242,   263,   264,   106,   107,
     108,   434,   110,    60,   114,   115,   717,   112,   240,   678,
     679,   680,   681,   682,   683,    62,   328,   368,   396,    90,
     114,   115,   718,   169,   436,   437,   334,   173,   338,    89,
     659,   660,   661,   662,   174,   663,   913,   339,   730,   914,
     915,   916,   176,   731,   730,   759,   398,   345,   346,   732,
     760,    89,   155,    89,   763,   431,   383,   880,   415,   764,
     765,   877,   881,   885,   162,   387,   397,   177,   895,   928,
     889,   205,   347,   896,   929,   867,   868,   869,   870,   196,
     348,   220,   359,   210,   367,   377,   378,   199,    89,   266,
     178,   246,   163,   222,   267,   401,   265,   237,   405,   407,
     268,   227,   438,   260,    89,   179,   406,   197,   278,   409,
     410,   211,   411,   412,   446,   301,   417,   420,   422,   194,
     423,   223,   426,   206,   427,   200,   239,   302,   114,   115,
     428,   261,   180,   221,   439,   201,   279,   440,   181,   228,
     536,   537,   538,   441,   442,   443,   445,   448,   447,   229,
     449,   240,   450,   241,   242,   303,   451,   243,   244,   245,
     452,   453,   457,   114,   115,   454,   455,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   456,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   468,   467,   469,   471,   472,   473,
     474,   476,    89,   596,   477,   478,   479,   480,   481,   482,
     635,   635,   483,   155,   485,   484,   486,   627,   627,   487,
     488,   490,   612,   491,   493,   162,   494,   495,   496,   497,
     694,   301,   498,   499,   501,   502,   503,    89,   504,   505,
     506,   507,   695,   302,   509,   513,   514,   517,   510,   511,
     516,   518,   520,   163,   519,   523,   521,   524,   522,   528,
     529,   531,   525,   526,   527,   533,   534,   535,   545,   539,
     696,   303,   540,   541,   542,   543,   544,   546,   547,   548,
     735,   552,    30,   551,   553,   554,   711,   566,   555,   556,
     557,   558,   567,   568,   569,   570,   578,   571,   572,   577,
     579,   580,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   597,   598,   599,   610,
     611,   643,   766,   647,   603,   651,   655,   671,   674,   703,
     707,   713,   723,   724,   725,   726,   727,   549,   738,   734,
     737,   741,   740,   743,   744,   751,   752,   784,   753,   754,
     755,   756,   757,   758,   771,   872,   770,   774,   773,   780,
     781,   776,   782,   783,   785,   787,   789,   786,   790,   844,
     788,   845,   847,   848,   905,   837,   838,   853,   893,   878,
     879,   839,   840,   883,   884,   890,   841,   842,   898,   900,
     902,   925,   873,   874,   875,   907,   926,   635,   876,   927,
     886,   930,   887,   581,   627,   642,   266,   177,   444,   803,
     246,   267,   888,   265,   821,   891,   798,   268,   904,   196,
     901,   820,   260,   613,   282,   278,   822,   199,   811,   931,
     178,   470,   906,   824,   932,   935,   813,   694,   791,   799,
     615,   826,   475,   205,   858,   179,   220,   197,   933,   695,
     261,   857,   818,   279,   800,   210,   812,   836,   222,   194,
     835,   825,   237,   859,   793,   200,   227,   792,   810,   817,
     843,   897,   180,   823,   814,   201,   515,   696,   181,   827,
     796,   801,   795,   211,   815,   794,   223,   802,   797,   828,
     508,   860,   512,   850,   852,   206,   849,   489,   221,   899,
     834,   846,   492,   851,   228,   701,   530,   614,   866,   903,
     532,   923,   934,     0,   229,   500,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   803,     0,     0,
       0,   821,     0,     0,   798,     0,     0,     0,   820,     0,
       0,     0,   858,   822,     0,     0,   811,     0,     0,   857,
     824,     0,     0,     0,   813,     0,     0,   799,   826,     0,
       0,   859,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   800,     0,   812,     0,     0,     0,   825,     0,
       0,     0,     0,     0,     0,     0,   810,     0,     0,   860,
     823,     0,   814,     0,     0,     0,   827,     0,     0,   801,
       0,     0,   815,     0,     0,   802,   828
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    74,    68,    69,    70,    71,    74,    73,    74,    75,
      76,    72,    74,    64,    68,    69,    70,    71,    10,    73,
      74,    71,    76,    69,   742,    71,    69,     5,   742,     7,
     742,     9,     0,    22,    23,    24,   742,   742,   148,    51,
       7,    69,    68,    69,    70,    71,    15,    73,    74,     3,
      76,    63,    64,    65,     8,    69,    70,    71,    89,    90,
      50,    69,    51,    71,    76,    12,    13,   124,    69,    16,
      11,    69,    19,    71,    69,    64,    65,    17,    18,    20,
      21,    22,    23,    24,    25,    26,     3,    76,     7,     6,
       6,    80,    81,    82,    83,    84,    85,     3,    87,     7,
       6,    42,    43,    44,    45,    46,    89,    90,     7,    50,
      51,     3,   119,   120,   121,   122,     8,    64,    65,     3,
      61,     3,     6,    64,    65,     3,     8,    64,    65,     3,
       8,   123,     3,     3,    75,    76,   148,     8,     8,    52,
     132,   133,   134,     3,   151,     7,     6,    88,   117,     7,
      91,    64,    65,    22,    23,    24,   148,    98,    99,   148,
       4,   102,   880,   100,   101,   148,   880,     8,   880,     7,
     148,   149,   150,   151,   880,   880,    21,    22,    23,    24,
      27,    50,    51,    52,     7,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    64,    65,    42,    43,    44,
       7,   148,    47,    48,    49,    52,    51,   148,    77,    14,
      15,   148,   125,     3,   127,   128,     7,    62,     8,    64,
      65,    66,    67,    68,    69,    70,    71,    21,    22,    23,
      24,     3,     3,    78,    79,   148,     8,     8,    72,    73,
      74,    86,    52,    53,    54,    55,    56,    57,    42,    43,
      44,     3,    46,     7,    64,    65,     8,    51,    52,    92,
      93,    94,    95,    96,    97,     7,     3,     3,     8,   335,
      64,    65,     8,    67,   325,   326,     4,    71,     4,   148,
      80,    81,    82,    83,    78,    85,   126,     4,     3,   129,
     130,   131,    86,     8,     3,     3,     8,     4,     4,     8,
       8,   148,   368,   148,     3,     3,     3,     3,     3,     8,
       8,     8,     8,     8,   368,     3,     3,   383,     3,     3,
       8,   387,     4,     8,     8,    28,    29,    30,    31,   383,
       4,   397,     4,   387,     4,     4,     4,   383,   148,   412,
     383,   407,   368,   397,   412,     4,   412,   397,     4,     3,
     412,   397,   148,   407,   148,   383,     8,   383,   412,     4,
       4,   387,     8,     3,   151,   431,     4,     4,     4,   383,
       4,   397,     4,   387,     4,   383,    27,   431,    64,    65,
       4,   407,   383,   397,     4,   383,   412,     4,   383,   397,
     441,   442,   443,     4,     4,     4,     4,     4,   151,   397,
       4,    52,     4,    54,    55,   431,     4,    58,    59,    60,
       4,   149,     4,    64,    65,   149,   149,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   149,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   149,     4,     4,     4,     4,
     151,     4,   148,   514,     4,     4,     4,     4,     4,     4,
     543,   544,   149,   539,     4,   151,     4,   543,   544,     4,
       4,     4,   533,     4,     4,   539,     4,     4,     4,     4,
     556,   557,     4,     4,     4,     4,   149,   148,     4,     4,
       4,   151,   556,   557,     4,     4,     4,     4,   151,   151,
     151,     4,     4,   539,   149,     4,   149,     4,   149,     4,
       4,     4,   151,   151,   151,     4,     7,     7,     5,     7,
     556,   557,   148,   148,   148,     7,     7,     5,     5,     5,
       3,     5,     7,   148,     5,     5,    87,   148,     7,     7,
       7,     5,   148,   148,     5,   148,     5,   148,   148,   148,
       7,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
       5,     7,   148,     7,   118,     7,     7,     7,     7,     7,
       7,     7,     4,     4,     4,     4,     4,   461,     3,     6,
       6,     3,     6,     6,     3,     6,     3,   149,     4,     4,
       4,     4,     4,     4,     3,   148,     6,     3,     6,     4,
       4,     8,     4,     4,   151,   151,     4,   149,     4,     4,
     149,     4,     6,     3,     5,   149,   149,     4,     4,     8,
       8,   149,   149,     8,     3,     8,   149,   149,     4,     4,
       4,     4,   148,   148,   148,     7,     4,   730,   148,     4,
     148,     4,   148,   491,   730,   544,   739,   733,   335,   742,
     736,   739,   148,   739,   747,   148,   742,   739,   148,   733,
     149,   747,   736,   534,   750,   739,   747,   733,   742,   151,
     733,   362,   148,   747,   149,   148,   742,   763,   730,   742,
     539,   747,   368,   769,   777,   733,   772,   733,   149,   763,
     736,   777,   745,   739,   742,   769,   742,   752,   772,   733,
     750,   747,   772,   777,   735,   733,   772,   733,   742,   744,
     759,   880,   733,   747,   742,   733,   415,   763,   733,   747,
     739,   742,   738,   769,   742,   736,   772,   742,   741,   747,
     407,   777,   412,   771,   774,   769,   769,   383,   772,   884,
     748,   763,   387,   772,   772,   557,   431,   535,   778,   895,
     434,   911,   928,    -1,   772,   397,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   880,    -1,    -1,
      -1,   884,    -1,    -1,   880,    -1,    -1,    -1,   884,    -1,
      -1,    -1,   895,   884,    -1,    -1,   880,    -1,    -1,   895,
     884,    -1,    -1,    -1,   880,    -1,    -1,   880,   884,    -1,
      -1,   895,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   880,    -1,   880,    -1,    -1,    -1,   884,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   880,    -1,    -1,   895,
     884,    -1,   880,    -1,    -1,    -1,   884,    -1,    -1,   880,
      -1,    -1,   880,    -1,    -1,   880,   884
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,     0,     5,
       7,     9,   148,   149,   150,   151,   167,   168,   169,   174,
       7,   183,     7,   189,     7,   203,     7,   279,     7,   360,
       7,   376,     7,   312,     7,   318,     7,   342,     7,   255,
       7,   429,     7,   464,   175,   170,   184,   190,   204,   280,
     361,   377,   313,   319,   343,   256,   430,   465,   167,   176,
     177,   148,   172,   173,    10,   123,   132,   133,   134,   148,
     182,   185,   186,   187,   456,   458,   460,   462,    11,    20,
      21,    22,    23,    24,    25,    26,    42,    43,    44,    45,
      46,    50,    51,    61,    64,    65,    75,    76,    88,    91,
      98,    99,   102,   182,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   214,   216,   240,   249,   263,   273,   302,
     310,   336,   366,   368,   381,   383,   385,   407,   418,   419,
     427,    12,    13,    16,    19,   182,   201,   202,   205,   207,
     210,   213,   366,   368,    47,    48,    49,    62,    66,    67,
      68,    69,    70,    71,    78,    79,    86,   182,   193,   194,
     195,   198,   281,   282,   283,   285,   287,   289,   291,   293,
     295,   297,   300,   301,   336,   354,   366,   368,   370,   381,
     383,   385,   403,    63,    76,   182,   336,   362,   363,   364,
     366,   368,   401,    80,    81,    82,    83,    84,    85,    87,
     182,   336,   366,   368,   378,   379,   380,   381,   383,   385,
     387,   389,   391,   393,   395,   397,   399,   401,   310,    27,
      52,    54,    55,    58,    59,    60,   182,   230,   320,   321,
     322,   323,   324,   325,   326,   328,   330,   332,   333,   335,
     366,   368,    53,    56,    57,   182,   230,   324,   330,   344,
     345,   346,   347,   348,   350,   351,   352,   353,   366,   368,
      89,    90,   182,   257,   258,   259,   261,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   182,   366,   368,   431,   432,   433,   434,   436,   438,
     439,   441,   442,   443,   446,   448,   449,   450,   451,   454,
     124,   466,   467,   468,     6,     3,     4,     8,     3,   188,
     463,   457,   459,   461,     4,     3,     8,   200,     4,     4,
     382,   384,   386,   215,   217,     4,     4,     4,     4,   274,
     311,   337,   303,   367,   369,   241,   408,   250,   264,     4,
     420,   428,     3,     8,   206,   208,   211,     4,     3,     8,
     286,   288,   290,   355,   284,   292,   294,     4,     4,   298,
     296,   371,   404,     3,     8,   365,   402,     3,     8,   390,
     392,   396,   394,   400,   398,   388,     8,     3,     8,   327,
     231,     4,   331,   329,   334,     4,     8,     3,   349,     4,
       4,     8,     3,   260,   262,     3,     8,     4,   435,   437,
       4,   440,     4,     4,   444,   447,     4,     4,     4,   452,
     455,     3,     8,   469,     3,     8,   167,   167,   148,     4,
       4,     4,     4,     4,   186,     4,   151,   151,     4,     4,
       4,     4,     4,   149,   149,   149,   149,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   149,     4,     4,
     192,     4,     4,     4,   151,   202,     4,     4,     4,     4,
       4,     4,     4,   149,   151,     4,     4,     4,     4,   282,
       4,     4,   363,     4,     4,     4,     4,     4,     4,     4,
     380,     4,     4,   149,     4,     4,     4,   151,   322,     4,
     151,   151,   346,     4,     4,   258,   151,     4,     4,   149,
       4,   149,   149,     4,     4,   151,   151,   151,     4,     4,
     432,     4,   467,     4,     7,     7,   167,   167,   167,     7,
     148,   148,   148,     7,     7,     5,     5,     5,     5,   169,
     171,   148,     5,     5,     5,     7,     7,     7,     5,   178,
      14,    15,   209,    17,    18,   212,   148,   148,   148,     5,
     148,   148,   148,    72,    73,    74,   299,   148,     5,     7,
     148,   178,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   167,   148,   148,   148,
      15,   117,   445,   118,   119,   120,   121,   122,   151,   453,
     148,     5,   167,   191,   466,   201,    27,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,   182,   218,   219,
     220,   223,   225,   227,   229,   230,   232,   233,   234,   235,
     236,   238,   218,     7,   275,   276,   277,     7,   314,   315,
     316,     7,   338,   339,   340,     7,   304,   305,   306,    80,
      81,    82,    83,    85,   242,   243,   244,   245,   246,   247,
     248,     7,   409,   410,     7,   251,   252,   253,    92,    93,
      94,    95,    96,    97,   265,   266,   267,   268,   269,   270,
     271,   272,   100,   101,   182,   366,   368,   421,   422,   423,
     425,   431,   179,     7,   356,   357,   358,     7,   372,   373,
     374,    87,   405,     7,   470,   471,     8,     8,     8,   221,
     224,   226,   228,     4,     4,     4,     4,     4,   237,   239,
       3,     8,     8,   278,     6,     3,   317,     6,     3,   341,
       6,     3,   307,     6,     3,     3,     6,   411,     3,     6,
     254,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   424,   426,     3,     8,     8,   148,   180,   181,   359,
       6,     3,   375,     6,     3,   406,     8,   472,     3,     6,
       4,     4,     4,     4,   149,   151,   149,   151,   149,     4,
       4,   219,   281,   277,   320,   316,   344,   340,   182,   193,
     194,   195,   198,   230,   273,   291,   295,   297,   308,   309,
     336,   366,   368,   381,   383,   385,   403,   306,   243,    77,
     182,   230,   310,   336,   366,   368,   381,   383,   385,   412,
     413,   414,   415,   416,   410,   257,   253,   149,   149,   149,
     149,   149,   149,   266,     4,     4,   422,     6,     3,   362,
     358,   378,   374,     4,   125,   127,   128,   182,   230,   366,
     368,   473,   474,   475,   476,   478,   471,    28,    29,    30,
      31,   222,   148,   148,   148,   148,   148,     8,     8,     8,
       3,     8,   417,     8,     3,     8,   148,   148,   148,     8,
       8,   148,   479,     4,   477,     3,     8,   309,     4,   414,
       4,   149,     4,   474,   148,     5,   148,     7,   480,   481,
     482,     3,     6,   126,   129,   130,   131,   483,   484,   485,
     487,   488,   489,   481,   486,     4,     4,     4,     3,     8,
       4,   151,   149,   149,   484,   148
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   152,   154,   153,   155,   153,   156,   153,   157,   153,
     158,   153,   159,   153,   160,   153,   161,   153,   162,   153,
     163,   153,   164,   153,   165,   153,   166,   153,   167,   167,
     167,   167,   167,   167,   167,   168,   170,   169,   171,   172,
     172,   173,   173,   175,   174,   176,   176,   177,   177,   179,
     178,   180,   180,   181,   181,   182,   184,   183,   185,   185,
     186,   186,   186,   186,   186,   186,   188,   187,   190,   189,
     191,   191,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   193,   194,
     195,   196,   197,   198,   200,   199,   201,   201,   202,   202,
     202,   202,   202,   202,   202,   204,   203,   206,   205,   208,
     207,   209,   209,   211,   210,   212,   212,   213,   215,   214,
     217,   216,   218,   218,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   221,   220,   222,
     222,   222,   222,   224,   223,   226,   225,   228,   227,   229,
     231,   230,   232,   233,   234,   235,   237,   236,   239,   238,
     241,   240,   242,   242,   243,   243,   243,   243,   243,   244,
     245,   246,   247,   248,   250,   249,   251,   251,   252,   252,
     254,   253,   256,   255,   257,   257,   257,   258,   258,   260,
     259,   262,   261,   264,   263,   265,   265,   266,   266,   266,
     266,   266,   266,   267,   268,   269,   270,   271,   272,   274,
     273,   275,   275,   276,   276,   278,   277,   280,   279,   281,
     281,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   284,   283,   286,   285,   288,
     287,   290,   289,   292,   291,   294,   293,   296,   295,   298,
     297,   299,   299,   299,   300,   301,   303,   302,   304,   304,
     305,   305,   307,   306,   308,   308,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   311,   310,   313,   312,   314,   314,   315,
     315,   317,   316,   319,   318,   320,   320,   321,   321,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   323,
     324,   325,   327,   326,   329,   328,   331,   330,   332,   334,
     333,   335,   337,   336,   338,   338,   339,   339,   341,   340,
     343,   342,   344,   344,   345,   345,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   347,   349,   348,   350,   351,
     352,   353,   355,   354,   356,   356,   357,   357,   359,   358,
     361,   360,   362,   362,   363,   363,   363,   363,   363,   363,
     365,   364,   367,   366,   369,   368,   371,   370,   372,   372,
     373,   373,   375,   374,   377,   376,   378,   378,   379,   379,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   382,   381,   384,   383,   386,
     385,   388,   387,   390,   389,   392,   391,   394,   393,   396,
     395,   398,   397,   400,   399,   402,   401,   404,   403,   406,
     405,   408,   407,   409,   409,   411,   410,   412,   412,   413,
     413,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   415,   417,   416,   418,   420,   419,   421,   421,   422,
     422,   422,   422,   422,   424,   423,   426,   425,   428,   427,
     430,   429,   431,   431,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   433,   435,   434,   437,   436,   438,   440,   439,   441,
     442,   444,   443,   445,   445,   447,   446,   448,   449,   450,
     452,   451,   453,   453,   453,   453,   453,   455,   454,   457,
     456,   459,   458,   461,   460,   463,   462,   465,   464,   466,
     466,   467,   469,   468,   470,   470,   472,   471,   473,   473,
     474,   474,   474,   474,   474,   474,   474,   475,   477,   476,
     479,   478,   480,   480,   482,   481,   483,   483,   484,   484,
     484,   484,   486,   485,   487,   488,   489
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     0,     4,     0,     4,
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
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "value",
  "sub_json", "map2", "$@14", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@15", "list_content", "not_empty_list", "list_strings",
  "$@16", "list_strings_content", "not_empty_list_strings",
  "unknown_map_entry", "syntax_map", "$@17", "global_objects",
  "global_object", "dhcp4_object", "$@18", "sub_dhcp4", "$@19",
  "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@20",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@21", "interfaces_list", "$@22", "dhcp_socket_type", "$@23",
  "socket_type", "outbound_interface", "$@24", "outbound_interface_value",
  "re_detect", "lease_database", "$@25", "hosts_database", "$@26",
  "database_map_params", "database_map_param", "database_type", "$@27",
  "db_type", "user", "$@28", "password", "$@29", "host", "$@30", "port",
  "name", "$@31", "persist", "lfc_interval", "readonly", "connect_timeout",
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
  "client_class_names_list", "$@85", "relay", "$@86", "relay_map", "$@87",
  "client_classes", "$@88", "client_classes_list", "client_class_entry",
  "$@89", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@90",
  "dhcp4o6_port", "control_socket", "$@91", "control_socket_params",
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
       0,   235,   235,   235,   236,   236,   237,   237,   238,   238,
     239,   239,   240,   240,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   245,   246,   246,   247,   247,   255,   256,
     257,   258,   259,   260,   261,   264,   269,   269,   280,   283,
     284,   287,   291,   298,   298,   305,   306,   309,   313,   320,
     320,   327,   328,   331,   335,   346,   356,   356,   372,   373,
     377,   378,   379,   380,   381,   382,   385,   385,   400,   400,
     409,   410,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   443,   448,
     453,   458,   463,   468,   474,   474,   485,   486,   489,   490,
     491,   492,   493,   494,   495,   498,   498,   507,   507,   517,
     517,   524,   525,   528,   528,   535,   537,   541,   547,   547,
     559,   559,   571,   572,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   590,   590,   597,
     598,   599,   600,   603,   603,   611,   611,   619,   619,   627,
     632,   632,   640,   645,   650,   655,   660,   660,   668,   668,
     677,   677,   687,   688,   691,   692,   693,   694,   695,   698,
     703,   708,   713,   718,   723,   723,   733,   734,   737,   738,
     741,   741,   751,   751,   761,   762,   763,   766,   767,   770,
     770,   778,   778,   786,   786,   797,   798,   801,   802,   803,
     804,   805,   806,   809,   814,   819,   824,   829,   834,   842,
     842,   855,   856,   859,   860,   867,   867,   893,   893,   904,
     905,   909,   910,   911,   912,   913,   914,   915,   916,   917,
     918,   919,   920,   921,   922,   923,   924,   925,   926,   927,
     928,   929,   930,   931,   932,   935,   935,   943,   943,   951,
     951,   959,   959,   967,   967,   975,   975,   983,   983,   991,
     991,   998,   999,  1000,  1003,  1008,  1015,  1015,  1026,  1027,
    1031,  1032,  1035,  1035,  1043,  1044,  1047,  1048,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,
    1061,  1062,  1063,  1070,  1070,  1083,  1083,  1092,  1093,  1096,
    1097,  1102,  1102,  1117,  1117,  1131,  1132,  1135,  1136,  1139,
    1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,  1151,
    1153,  1158,  1160,  1160,  1168,  1168,  1176,  1176,  1184,  1186,
    1186,  1194,  1203,  1203,  1215,  1216,  1221,  1222,  1227,  1227,
    1239,  1239,  1251,  1252,  1257,  1258,  1263,  1264,  1265,  1266,
    1267,  1268,  1269,  1270,  1271,  1274,  1276,  1276,  1284,  1286,
    1288,  1293,  1301,  1301,  1313,  1314,  1317,  1318,  1321,  1321,
    1331,  1331,  1341,  1342,  1345,  1346,  1347,  1348,  1349,  1350,
    1353,  1353,  1361,  1361,  1386,  1386,  1416,  1416,  1426,  1427,
    1430,  1431,  1434,  1434,  1443,  1443,  1452,  1453,  1456,  1457,
    1461,  1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,  1470,
    1471,  1472,  1473,  1474,  1475,  1478,  1478,  1486,  1486,  1494,
    1494,  1502,  1502,  1510,  1510,  1518,  1518,  1526,  1526,  1534,
    1534,  1542,  1542,  1550,  1550,  1558,  1558,  1571,  1571,  1581,
    1581,  1592,  1592,  1602,  1603,  1606,  1606,  1616,  1617,  1620,
    1621,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,
    1633,  1636,  1638,  1638,  1650,  1657,  1657,  1667,  1668,  1671,
    1672,  1673,  1674,  1675,  1678,  1678,  1686,  1686,  1696,  1696,
    1708,  1708,  1718,  1719,  1722,  1723,  1724,  1725,  1726,  1727,
    1728,  1729,  1730,  1731,  1732,  1733,  1734,  1735,  1736,  1737,
    1738,  1741,  1746,  1746,  1754,  1754,  1762,  1767,  1767,  1775,
    1780,  1785,  1785,  1793,  1794,  1797,  1797,  1805,  1810,  1815,
    1820,  1820,  1828,  1831,  1834,  1837,  1840,  1846,  1846,  1856,
    1856,  1863,  1863,  1870,  1870,  1882,  1882,  1892,  1892,  1903,
    1904,  1908,  1912,  1912,  1924,  1925,  1929,  1929,  1937,  1938,
    1941,  1942,  1943,  1944,  1945,  1946,  1947,  1950,  1955,  1955,
    1963,  1963,  1973,  1974,  1977,  1977,  1985,  1986,  1989,  1990,
    1991,  1992,  1995,  1995,  2003,  2008,  2013
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
#line 4493 "dhcp4_parser.cc" // lalr1.cc:1167
#line 2018 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
