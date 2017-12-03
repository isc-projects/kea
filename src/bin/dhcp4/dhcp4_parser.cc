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
      case 447: // ncr_protocol_value
      case 455: // replace_client_name_value
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
      case 447: // ncr_protocol_value
      case 455: // replace_client_name_value
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

      case 447: // ncr_protocol_value

#line 226 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 436 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 455: // replace_client_name_value

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
      case 447: // ncr_protocol_value
      case 455: // replace_client_name_value
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

  case 389:
#line 1352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2290 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2300 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1360 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1362 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
    e->set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.stack_.back()->combine_set("user-context", e);
    ctx.leave();
}
#line 2336 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1379 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2347 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1384 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1397 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2375 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2394 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2402 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2412 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 426:
#line 1449 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2420 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 427:
#line 1451 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2430 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2438 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2448 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 430:
#line 1465 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2456 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2466 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1473 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2474 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2484 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1481 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1483 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1489 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2510 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1497 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2538 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1505 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2546 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2556 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2564 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1515 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2574 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1521 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2585 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1526 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2594 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2605 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1539 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2614 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1544 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2622 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1546 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2632 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1555 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2643 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 451:
#line 1560 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2652 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1569 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2662 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2672 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1603 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2690 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1625 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2719 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1641 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2727 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1643 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2737 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1649 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2745 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1651 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2755 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2763 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2772 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2794 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2804 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2814 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1713 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2823 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2831 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1720 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2841 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2868 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2886 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1757 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2912 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1759 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2921 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2927 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2933 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1769 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2941 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2951 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2960 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2969 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1787 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2986 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1794 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2995 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1800 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1803 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1806 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3019 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1812 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1820 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1828 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1830 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3071 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1835 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3079 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1837 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1842 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3096 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3105 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1859 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3125 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1864 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3135 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1868 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1884 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3154 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3173 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1905 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3181 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1922 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3190 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3198 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 571:
#line 1929 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3208 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1935 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3219 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1940 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3228 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1949 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3238 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1953 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3246 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 1967 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3254 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 1969 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3264 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 1975 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3273 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3282 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3291 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3295 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -745;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
     305,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,    16,    36,    47,    61,    79,    82,
     106,   117,   132,   159,   182,   184,   188,   195,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,    36,    20,     9,   183,    72,    52,
      14,   213,   142,   356,    -4,    -8,   323,    86,  -745,   224,
     229,   234,   238,   247,  -745,  -745,  -745,  -745,  -745,   259,
    -745,    55,  -745,  -745,  -745,  -745,  -745,  -745,  -745,   266,
     269,  -745,  -745,  -745,  -745,  -745,   286,   287,   295,   299,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
     303,  -745,  -745,  -745,    63,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,   309,  -745,    84,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,   313,   315,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,    90,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,    94,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,   253,   277,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,   301,  -745,
    -745,   325,  -745,  -745,  -745,   342,  -745,  -745,   319,   341,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,   345,   350,  -745,  -745,  -745,  -745,   347,
     362,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,   125,  -745,  -745,  -745,   365,  -745,  -745,
     371,  -745,   372,   374,  -745,  -745,   376,   377,   385,  -745,
    -745,  -745,  -745,  -745,   185,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,   208,  -745,  -745,  -745,    36,    36,  -745,   242,   391,
     393,   402,   403,   405,  -745,     9,  -745,   408,   267,   268,
     413,   418,   419,   420,   421,   304,   306,   307,   310,   450,
     453,   454,   456,   457,   458,   459,   460,   461,   462,   318,
     464,   465,   183,  -745,   466,   468,   469,   324,    72,  -745,
     191,   470,   472,   473,   474,   475,   477,   478,   334,   333,
     481,   482,   483,   484,    52,  -745,   486,    14,  -745,   487,
     488,   491,   492,   496,   497,   498,   499,  -745,   213,  -745,
     501,   504,   361,   507,   508,   509,   363,  -745,   356,   511,
     366,   368,  -745,    -4,   512,   516,   -43,  -745,   373,   519,
     524,   380,   526,   382,   383,   529,   530,   384,   386,   389,
     532,   537,   323,  -745,   538,    86,  -745,  -745,  -745,   539,
     540,   541,    36,    36,    36,  -745,   542,  -745,  -745,   396,
     397,   398,   544,   545,  -745,  -745,  -745,  -745,   548,   549,
     550,   551,   552,    36,   553,   555,   556,   557,  -745,   558,
     559,  -745,   562,   166,   135,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,   554,   560,  -745,
    -745,  -745,   409,   423,   424,   563,   425,   426,   427,  -745,
    -745,   285,   428,   564,   571,  -745,   431,  -745,   562,   432,
     433,   435,   436,   438,   439,   440,  -745,   441,   442,  -745,
     443,   444,   445,  -745,  -745,   446,  -745,  -745,  -745,   447,
      36,  -745,  -745,   448,   449,  -745,   451,  -745,  -745,    -9,
     480,  -745,  -745,  -745,   102,   452,  -745,   596,  -745,    36,
     183,    86,  -745,  -745,  -745,    72,  -745,  -745,  -745,   138,
     138,   595,   597,   598,   599,  -745,  -745,  -745,   116,    37,
     600,   308,   118,   323,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,   604,  -745,   191,  -745,  -745,  -745,   602,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,   603,   525,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
     606,  -745,   237,   246,   254,  -745,  -745,  -745,  -745,   607,
     610,   611,   612,   613,  -745,  -745,  -745,   257,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,   264,  -745,   614,   615,  -745,  -745,   616,   618,  -745,
    -745,   617,   621,  -745,  -745,   619,   623,  -745,  -745,  -745,
    -745,  -745,  -745,    26,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,    77,  -745,   622,   624,  -745,   625,   626,   627,   628,
     629,   630,   276,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,   280,  -745,  -745,  -745,  -745,
    -745,   284,   455,   471,  -745,  -745,   631,   632,  -745,  -745,
     633,   635,  -745,  -745,   634,  -745,   143,  -745,  -745,  -745,
    -745,   636,   637,   639,   640,   500,   485,   502,   494,   503,
     642,   643,   138,  -745,  -745,    52,  -745,   595,   356,  -745,
     597,    -4,  -745,   598,    83,  -745,   599,   116,  -745,    37,
    -745,    -8,  -745,   600,   505,   506,   510,   513,   514,   515,
     308,  -745,   644,   646,   649,   118,  -745,  -745,  -745,   650,
     654,  -745,    14,  -745,   602,   213,  -745,   603,   656,  -745,
     187,   606,  -745,    81,   517,   518,   520,  -745,  -745,  -745,
    -745,  -745,   521,   522,  -745,   298,  -745,   653,  -745,   659,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,   302,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,   317,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,    36,   523,   527,  -745,  -745,   528,   320,  -745,
     664,  -745,   531,  -745,   669,  -745,  -745,  -745,  -745,  -745,
     337,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,    83,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,   670,
     533,   673,   187,  -745,  -745,   675,  -745,   535,  -745,   651,
    -745,  -745,   161,  -745,    29,   651,  -745,  -745,   674,   677,
     680,   340,  -745,  -745,  -745,  -745,  -745,  -745,   681,   543,
     565,   567,    29,  -745,   569,  -745,  -745,  -745,  -745,  -745
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    68,     7,   115,     9,   227,    11,   380,    13,
     403,    15,   305,    17,   313,    19,   350,    21,   192,    23,
     492,    25,   549,    27,    45,    39,     0,     0,     0,     0,
       0,   405,     0,   315,   352,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    66,   547,   541,   543,   545,     0,
      65,     0,    58,    60,    62,    63,    64,    61,   104,     0,
       0,   424,   426,   428,   128,   130,     0,     0,     0,     0,
     219,   303,   342,   276,   391,   393,   170,   450,   184,   203,
       0,   474,   490,    97,     0,    70,    72,    73,    74,    75,
      90,    91,    78,    79,    80,    81,    85,    86,    76,    77,
      83,    84,    95,    96,    92,    93,    94,    82,    87,    88,
      89,   117,   119,   123,     0,   114,     0,   106,   108,   109,
     110,   111,   112,   113,   454,   257,   259,   261,   372,   255,
     263,   265,     0,     0,   269,   267,   395,   446,   254,   231,
     232,   233,   245,     0,   229,   236,   249,   250,   251,   237,
     238,   241,   243,   239,   240,   234,   235,   252,   253,   242,
     246,   247,   248,   244,   389,   388,   385,     0,   382,   384,
     386,   387,   444,   432,   434,   438,   436,   442,   440,   430,
     423,   417,   421,   422,     0,   406,   407,   418,   419,   420,
     414,   409,   415,   411,   412,   413,   416,   410,     0,   332,
     160,     0,   336,   334,   339,     0,   328,   329,     0,   316,
     317,   319,   331,   320,   321,   322,   338,   323,   324,   325,
     326,   327,   366,     0,     0,   364,   365,   368,   369,     0,
     353,   354,   356,   357,   358,   359,   360,   361,   362,   363,
     199,   201,   196,     0,   194,   197,   198,     0,   514,   516,
       0,   519,     0,     0,   523,   527,     0,     0,     0,   532,
     539,   512,   510,   511,     0,   494,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     554,     0,   551,   553,    44,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    55,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,   116,
     456,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   228,     0,     0,   381,     0,
       0,     0,     0,     0,     0,     0,     0,   404,     0,   306,
       0,     0,     0,     0,     0,     0,     0,   314,     0,     0,
       0,     0,   351,     0,     0,     0,     0,   193,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   493,     0,     0,   550,    48,    41,     0,
       0,     0,     0,     0,     0,    59,     0,   102,   103,     0,
       0,     0,     0,     0,    98,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   473,     0,
       0,    71,     0,     0,     0,   127,   107,   471,   469,   470,
     462,   463,   467,   468,   464,   465,   466,     0,   457,   458,
     460,   461,     0,     0,     0,     0,     0,     0,     0,   274,
     275,     0,     0,     0,     0,   230,     0,   383,     0,     0,
       0,     0,     0,     0,     0,     0,   408,     0,     0,   330,
       0,     0,     0,   341,   318,     0,   370,   371,   355,     0,
       0,   195,   513,     0,     0,   518,     0,   521,   522,     0,
       0,   529,   530,   531,     0,     0,   495,     0,   552,     0,
       0,     0,   542,   544,   546,     0,   425,   427,   429,     0,
       0,   221,   307,   344,   278,    38,   392,   394,     0,     0,
     186,     0,     0,     0,    49,   118,   121,   122,   120,   125,
     126,   124,     0,   455,     0,   258,   260,   262,   374,   256,
     264,   266,   271,   272,   273,   270,   268,   397,     0,   390,
     445,   433,   435,   439,   437,   443,   441,   431,   333,   161,
     337,   335,   340,   367,   200,   202,   515,   517,   520,   525,
     526,   524,   528,   534,   535,   536,   537,   538,   533,   540,
       0,    42,     0,     0,     0,   147,   153,   155,   157,     0,
       0,     0,     0,     0,   166,   168,   146,     0,   132,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,     0,   225,     0,   222,   223,   311,     0,   308,   309,
     348,     0,   345,   346,   282,     0,   279,   280,   179,   180,
     181,   182,   183,     0,   172,   174,   175,   176,   177,   178,
     452,     0,   190,     0,   187,   188,     0,     0,     0,     0,
       0,     0,     0,   205,   207,   208,   209,   210,   211,   212,
     488,   483,   485,   482,   487,     0,   476,   478,   479,   480,
     481,     0,    51,     0,   459,   378,     0,   375,   376,   401,
       0,   398,   399,   448,     0,   558,     0,   556,    67,   548,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   131,     0,   220,     0,   315,   304,
       0,   352,   343,     0,     0,   277,     0,     0,   171,     0,
     451,     0,   185,     0,     0,     0,     0,     0,     0,     0,
       0,   204,     0,     0,     0,     0,   475,   491,    53,     0,
      52,   472,     0,   373,     0,   405,   396,     0,     0,   447,
       0,     0,   555,     0,     0,     0,     0,   159,   162,   163,
     164,   165,     0,     0,   133,     0,   224,     0,   310,     0,
     347,   302,   299,   289,   290,   292,   286,   287,   288,   298,
     297,     0,   284,   291,   300,   301,   293,   294,   295,   296,
     281,   173,   453,     0,   189,   213,   214,   215,   216,   217,
     218,   206,     0,     0,     0,   477,    50,     0,     0,   377,
       0,   400,     0,   572,     0,   570,   568,   562,   566,   567,
       0,   560,   564,   565,   563,   557,   149,   150,   151,   152,
     148,   154,   156,   158,   167,   169,   226,   312,   349,     0,
     283,   191,   489,   484,   486,    54,   379,   402,   449,     0,
       0,     0,     0,   559,   285,     0,   569,     0,   561,     0,
     571,   576,     0,   574,     0,     0,   573,   584,     0,     0,
       0,     0,   578,   580,   581,   582,   583,   575,     0,     0,
       0,     0,     0,   577,     0,   586,   587,   588,   579,   585
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,   -50,  -745,   226,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,   192,  -745,  -745,  -745,
     -66,  -745,  -745,  -745,   358,  -745,  -745,  -745,  -745,   141,
     349,   -68,   -58,   -54,  -745,  -745,   -51,  -745,  -745,   148,
     339,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,   162,   -29,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,   -62,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,   -42,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,   -45,  -745,  -745,  -745,   -40,   316,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,   -47,  -745,  -745,  -745,  -745,  -745,
    -745,  -744,  -745,  -745,  -745,   -22,  -745,  -745,  -745,   -19,
     353,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -738,
    -745,  -745,  -745,  -552,  -745,  -733,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,   -26,  -745,  -745,  -147,   -59,  -745,
    -745,  -745,  -745,  -745,   -17,  -745,  -745,  -745,   -13,  -745,
     336,  -745,   -53,  -745,  -745,  -745,  -745,  -745,   -41,  -745,
    -745,  -745,  -745,  -745,   -14,  -745,  -745,  -745,   -16,  -745,
    -745,  -745,   -10,  -745,   346,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,   -39,  -745,  -745,  -745,
     -32,   381,  -745,  -745,   -46,  -745,   -34,  -745,  -745,  -745,
    -745,  -745,   -33,  -745,  -745,  -745,   -28,  -745,   354,    -7,
    -745,    -2,  -745,     1,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -726,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,   179,  -745,  -745,  -745,  -745,  -745,  -745,  -745,   -15,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,   196,   343,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,  -745,
    -745,  -745,  -745,  -745,  -745,  -745,   220,   338,  -745,  -745,
    -745,   -27,  -745,  -745,  -130,  -745,  -745,  -745,  -745,  -745,
    -745,  -139,  -745,  -745,  -155,  -745,  -745,  -745,  -745,  -745
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   566,
      82,    83,    39,    64,    79,    80,   575,   722,   789,   790,
     123,    41,    66,    91,    92,    93,   329,    43,    67,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   337,   156,
     157,    45,    68,   158,   364,   159,   365,   578,   160,   366,
     581,   161,   133,   343,   134,   344,   647,   648,   649,   741,
     880,   650,   742,   651,   743,   652,   744,   653,   247,   401,
     655,   656,   657,   658,   659,   750,   660,   751,   135,   355,
     683,   684,   685,   686,   687,   688,   689,   136,   357,   693,
     694,   695,   771,    59,    75,   283,   284,   285,   414,   286,
     415,   137,   358,   702,   703,   704,   705,   706,   707,   708,
     709,   138,   349,   663,   664,   665,   755,    47,    69,   183,
     184,   185,   375,   186,   371,   187,   372,   188,   373,   189,
     376,   190,   377,   191,   381,   192,   380,   595,   193,   194,
     139,   352,   675,   676,   677,   764,   831,   832,   140,   350,
      53,    72,   667,   668,   669,   758,    55,    73,   248,   249,
     250,   251,   252,   253,   254,   400,   255,   404,   256,   403,
     257,   258,   405,   259,   141,   351,   671,   672,   673,   761,
      57,    74,   269,   270,   271,   272,   273,   409,   274,   275,
     276,   277,   196,   374,   726,   727,   728,   792,    49,    70,
     207,   208,   209,   386,   142,   353,   143,   354,   199,   382,
     730,   731,   732,   795,    51,    71,   224,   225,   226,   144,
     340,   145,   341,   146,   342,   230,   396,   231,   390,   232,
     391,   233,   393,   234,   392,   235,   395,   236,   394,   237,
     389,   203,   383,   734,   798,   147,   356,   691,   370,   487,
     488,   489,   490,   491,   582,   148,   149,   360,   715,   716,
     717,   783,   718,   784,   719,   720,   782,   150,   361,    61,
      76,   304,   305,   306,   307,   419,   308,   420,   309,   310,
     422,   311,   312,   313,   425,   621,   314,   426,   315,   316,
     317,   318,   430,   628,   319,   431,    94,   331,    95,   332,
      96,   333,    97,   330,    63,    77,   321,   322,   323,   434,
     736,   737,   800,   870,   871,   872,   873,   901,   874,   899,
     912,   913,   914,   921,   922,   923,   928,   924,   925,   926
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      90,   179,   155,   178,   205,   220,   619,   246,   265,   282,
     301,   180,   266,   238,    78,   181,    28,   690,   182,    84,
     827,   267,   162,   197,   210,   222,   828,   260,   278,   767,
     302,   830,   768,   268,   163,   198,   211,   223,   839,   261,
     279,    29,   303,    30,   164,    31,   280,   281,   240,   262,
     241,   242,   263,   264,    40,   195,   206,   221,   335,   164,
     114,   115,   200,   336,   227,   112,   362,   201,    42,   228,
     202,   363,   229,   100,   101,   102,   103,   204,   114,   115,
     769,   280,   281,   770,   151,   152,    44,   368,   153,    46,
     164,   154,   369,   384,   106,   107,   108,   387,   385,   165,
     166,   167,   388,   112,   100,   101,   102,   103,   620,   876,
     877,   878,   879,    48,   168,   175,   114,   115,   169,   170,
     171,   172,   173,   174,    50,   106,   107,   108,   416,   110,
     175,   176,    85,   417,   112,   240,   114,   115,   177,    52,
      89,    86,    87,    88,    89,   827,   801,   114,   115,   802,
     170,   828,   579,   580,   174,   917,   830,    89,   918,   919,
     920,   175,    89,   839,   915,   635,    54,   916,    81,   177,
     636,   637,   638,   639,   640,   641,   642,   643,   644,   645,
     576,   577,   114,   710,    32,    33,    34,    35,   432,    56,
     240,    58,   111,   433,    98,    60,   678,   679,   680,   681,
      89,   682,    62,    99,   100,   101,   102,   103,   104,   105,
     320,   435,   829,   101,   102,   103,   436,   842,   711,   712,
      89,   623,   624,   625,   626,   106,   107,   108,   109,   110,
     324,    89,   325,   111,   112,   101,   102,   103,   326,   240,
     362,   111,   112,   240,   113,   738,   327,   114,   115,   435,
     328,   114,   115,   627,   739,   114,   115,   368,   116,   117,
     752,   397,   740,   334,   112,   753,    89,   752,   477,    90,
     338,   118,   754,   339,   119,   437,   438,   114,   115,   780,
     398,   120,   121,   785,   781,   122,    89,   432,   786,   212,
     345,   346,   787,   213,   214,   215,   216,   217,   218,   347,
     219,   384,   155,   348,   478,   889,   886,   359,   479,   399,
     890,   480,   863,   367,   864,   865,   179,   378,   178,   379,
     416,   205,   162,   387,   482,   891,   180,   407,   896,   402,
     181,    89,   220,   182,   163,    89,   483,   829,   197,    89,
     902,   210,   246,   932,   408,   903,   406,   265,   933,   410,
     198,   266,   222,   211,   411,   412,   481,   592,   593,   594,
     267,    89,   260,   484,   223,   413,   301,   278,   485,   418,
     195,   486,   268,   206,   261,   421,   423,   200,   424,   279,
     427,   428,   201,   239,   221,   202,   302,   114,   115,   429,
     439,   227,   552,   553,   554,   440,   228,   441,   303,   229,
     696,   697,   698,   699,   700,   701,   442,   443,   240,   444,
     241,   242,   446,   567,   243,   244,   245,   449,   447,   448,
     114,   115,   450,   451,   452,   453,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   454,   458,   455,   456,   459,   460,   457,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     472,    89,   473,   474,   492,   475,   493,   494,   495,   496,
     615,   497,   498,   499,   500,   501,   502,   503,   504,   155,
     506,   508,   509,   646,   646,   510,   511,   654,   654,   631,
     512,   513,   514,   515,    89,   517,   713,   301,   518,   162,
     519,   520,   521,   522,   523,   525,   529,   526,   478,   527,
     530,   163,   479,   533,   532,   480,   714,   302,   534,   535,
     536,   537,   538,   539,   540,   541,   544,   542,   482,   303,
     543,   545,   547,   549,   556,   557,   558,   550,   551,   555,
     483,   559,   560,   561,   562,   563,   564,   585,   568,    30,
     569,   570,   583,   584,   571,   572,   573,   574,   588,   597,
     481,   586,   587,   589,   590,   591,   596,   484,   598,   599,
     601,   602,   485,   603,   604,   486,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   616,   617,   622,   618,
     629,   630,   662,   788,   666,   670,   674,   692,   723,   725,
     729,   745,   733,   735,   746,   747,   748,   749,   757,   791,
     756,   760,   759,   762,   763,   765,   766,   773,   772,   774,
     775,   776,   777,   778,   779,   794,   808,   793,   797,   796,
     803,   804,   799,   805,   806,   810,   812,   813,   852,   807,
     853,   809,   811,   854,   845,   846,   856,   857,   911,   847,
     862,   887,   848,   849,   850,   881,   882,   888,   883,   884,
     885,   893,   897,   900,   905,   894,   895,   907,   929,   898,
     909,   930,   906,   910,   931,   934,   646,   179,   565,   178,
     654,   632,   246,   445,   935,   265,   822,   180,   821,   266,
     600,   181,   826,   634,   182,   282,   823,   476,   267,   197,
     824,   471,   260,   825,   936,   278,   937,   939,   834,   713,
     268,   198,   661,   814,   261,   841,   205,   279,   844,   220,
     835,   843,   531,   851,   866,   816,   815,   505,   867,   714,
     840,   195,   904,   818,   524,   817,   210,   820,   200,   222,
     833,   819,   516,   201,   868,   859,   202,   836,   211,   528,
     858,   223,   837,   724,   861,   838,   869,   860,   507,   721,
     855,   633,   908,   548,   875,   546,   927,   938,   206,     0,
       0,   221,     0,     0,     0,     0,     0,     0,   227,     0,
       0,     0,     0,   228,     0,     0,   229,     0,     0,     0,
       0,     0,   892,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   822,     0,   821,     0,     0,     0,   826,     0,     0,
       0,   823,     0,     0,     0,   824,   866,     0,   825,     0,
     867,     0,     0,   834,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   835,   868,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   869,     0,
       0,     0,     0,     0,     0,   833,     0,     0,     0,     0,
       0,     0,   836,     0,     0,     0,     0,   837,     0,     0,
     838
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      66,    69,    68,    69,    70,    71,    15,    73,    74,    75,
      76,    69,    74,    72,    64,    69,     0,   569,    69,    10,
     764,    74,    68,    69,    70,    71,   764,    73,    74,     3,
      76,   764,     6,    74,    68,    69,    70,    71,   764,    73,
      74,     5,    76,     7,     7,     9,    89,    90,    52,    53,
      54,    55,    56,    57,     7,    69,    70,    71,     3,     7,
      64,    65,    69,     8,    71,    51,     3,    69,     7,    71,
      69,     8,    71,    21,    22,    23,    24,    63,    64,    65,
       3,    89,    90,     6,    12,    13,     7,     3,    16,     7,
       7,    19,     8,     3,    42,    43,    44,     3,     8,    47,
      48,    49,     8,    51,    21,    22,    23,    24,   117,    28,
      29,    30,    31,     7,    62,    78,    64,    65,    66,    67,
      68,    69,    70,    71,     7,    42,    43,    44,     3,    46,
      78,    79,   123,     8,    51,    52,    64,    65,    86,     7,
     148,   132,   133,   134,   148,   889,     3,    64,    65,     6,
      67,   889,    17,    18,    71,   126,   889,   148,   129,   130,
     131,    78,   148,   889,     3,    27,     7,     6,   148,    86,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      14,    15,    64,    65,   148,   149,   150,   151,     3,     7,
      52,     7,    50,     8,    11,     7,    80,    81,    82,    83,
     148,    85,     7,    20,    21,    22,    23,    24,    25,    26,
     124,     3,   764,    22,    23,    24,     8,   769,   100,   101,
     148,   119,   120,   121,   122,    42,    43,    44,    45,    46,
       6,   148,     3,    50,    51,    22,    23,    24,     4,    52,
       3,    50,    51,    52,    61,     8,     8,    64,    65,     3,
       3,    64,    65,   151,     8,    64,    65,     3,    75,    76,
       3,     8,     8,     4,    51,     8,   148,     3,    77,   335,
       4,    88,     8,     4,    91,   325,   326,    64,    65,     3,
       3,    98,    99,     3,     8,   102,   148,     3,     8,    76,
       4,     4,     8,    80,    81,    82,    83,    84,    85,     4,
      87,     3,   368,     4,   370,     3,     8,     4,   370,     8,
       8,   370,   125,     4,   127,   128,   384,     4,   384,     4,
       3,   387,   368,     3,   370,     8,   384,     8,     8,     4,
     384,   148,   398,   384,   368,   148,   370,   889,   384,   148,
       3,   387,   408,     3,     3,     8,     4,   413,     8,     4,
     384,   413,   398,   387,     4,     8,   370,    72,    73,    74,
     413,   148,   408,   370,   398,     3,   432,   413,   370,     4,
     384,   370,   413,   387,   408,     4,     4,   384,     4,   413,
       4,     4,   384,    27,   398,   384,   432,    64,    65,     4,
     148,   398,   442,   443,   444,     4,   398,     4,   432,   398,
      92,    93,    94,    95,    96,    97,     4,     4,    52,     4,
      54,    55,     4,   463,    58,    59,    60,     4,   151,   151,
      64,    65,     4,     4,     4,     4,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   149,     4,   149,   149,     4,     4,   149,
       4,     4,     4,     4,     4,     4,     4,   149,     4,     4,
       4,   148,     4,     4,     4,   151,     4,     4,     4,     4,
     530,     4,     4,   149,   151,     4,     4,     4,     4,   555,
       4,     4,     4,   559,   560,     4,     4,   559,   560,   549,
       4,     4,     4,     4,   148,     4,   572,   573,     4,   555,
     149,     4,     4,     4,   151,     4,     4,   151,   584,   151,
       4,   555,   584,     4,   151,   584,   572,   573,     4,   149,
       4,   149,   149,     4,     4,   151,     4,   151,   584,   573,
     151,     4,     4,     4,   148,   148,   148,     7,     7,     7,
     584,     7,     7,     5,     5,     5,     5,   148,     5,     7,
       5,     5,     8,     3,     7,     7,     7,     5,     5,     5,
     584,   148,   148,   148,   148,   148,   148,   584,     7,   148,
     148,   148,   584,   148,   148,   584,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   118,   148,
     148,     5,     7,   148,     7,     7,     7,     7,     4,     7,
       7,     4,    87,     7,     4,     4,     4,     4,     3,   148,
       6,     3,     6,     6,     3,     6,     3,     3,     6,     4,
       4,     4,     4,     4,     4,     3,   151,     6,     3,     6,
       4,     4,     8,     4,     4,   151,     4,     4,     4,   149,
       4,   149,   149,     4,   149,   149,     6,     3,     7,   149,
       4,     8,   149,   149,   149,   148,   148,     8,   148,   148,
     148,   148,     8,     4,     4,   148,   148,     4,     4,   148,
       5,     4,   149,   148,     4,     4,   752,   755,   462,   755,
     752,   550,   758,   335,   151,   761,   764,   755,   764,   761,
     508,   755,   764,   555,   755,   771,   764,   368,   761,   755,
     764,   362,   758,   764,   149,   761,   149,   148,   764,   785,
     761,   755,   560,   752,   758,   767,   792,   761,   773,   795,
     764,   771,   416,   780,   800,   757,   755,   384,   800,   785,
     766,   755,   889,   760,   408,   758,   792,   763,   755,   795,
     764,   761,   398,   755,   800,   794,   755,   764,   792,   413,
     792,   795,   764,   584,   797,   764,   800,   795,   387,   573,
     785,   551,   902,   435,   801,   432,   915,   932,   792,    -1,
      -1,   795,    -1,    -1,    -1,    -1,    -1,    -1,   795,    -1,
      -1,    -1,    -1,   795,    -1,    -1,   795,    -1,    -1,    -1,
      -1,    -1,   852,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   889,    -1,   889,    -1,    -1,    -1,   889,    -1,    -1,
      -1,   889,    -1,    -1,    -1,   889,   902,    -1,   889,    -1,
     902,    -1,    -1,   889,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   889,   902,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   902,    -1,
      -1,    -1,    -1,    -1,    -1,   889,    -1,    -1,    -1,    -1,
      -1,    -1,   889,    -1,    -1,    -1,    -1,   889,    -1,    -1,
     889
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
       7,   431,     7,   466,   175,   170,   184,   190,   204,   280,
     361,   377,   313,   319,   343,   256,   432,   467,   167,   176,
     177,   148,   172,   173,    10,   123,   132,   133,   134,   148,
     182,   185,   186,   187,   458,   460,   462,   464,    11,    20,
      21,    22,    23,    24,    25,    26,    42,    43,    44,    45,
      46,    50,    51,    61,    64,    65,    75,    76,    88,    91,
      98,    99,   102,   182,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   214,   216,   240,   249,   263,   273,   302,
     310,   336,   366,   368,   381,   383,   385,   407,   417,   418,
     429,    12,    13,    16,    19,   182,   201,   202,   205,   207,
     210,   213,   366,   368,     7,    47,    48,    49,    62,    66,
      67,    68,    69,    70,    71,    78,    79,    86,   182,   193,
     194,   195,   198,   281,   282,   283,   285,   287,   289,   291,
     293,   295,   297,   300,   301,   336,   354,   366,   368,   370,
     381,   383,   385,   403,    63,   182,   336,   362,   363,   364,
     366,   368,    76,    80,    81,    82,    83,    84,    85,    87,
     182,   336,   366,   368,   378,   379,   380,   381,   383,   385,
     387,   389,   391,   393,   395,   397,   399,   401,   310,    27,
      52,    54,    55,    58,    59,    60,   182,   230,   320,   321,
     322,   323,   324,   325,   326,   328,   330,   332,   333,   335,
     366,   368,    53,    56,    57,   182,   230,   324,   330,   344,
     345,   346,   347,   348,   350,   351,   352,   353,   366,   368,
      89,    90,   182,   257,   258,   259,   261,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   182,   366,   368,   433,   434,   435,   436,   438,   440,
     441,   443,   444,   445,   448,   450,   451,   452,   453,   456,
     124,   468,   469,   470,     6,     3,     4,     8,     3,   188,
     465,   459,   461,   463,     4,     3,     8,   200,     4,     4,
     382,   384,   386,   215,   217,     4,     4,     4,     4,   274,
     311,   337,   303,   367,   369,   241,   408,   250,   264,     4,
     419,   430,     3,     8,   206,   208,   211,     4,     3,     8,
     410,   286,   288,   290,   355,   284,   292,   294,     4,     4,
     298,   296,   371,   404,     3,     8,   365,     3,     8,   402,
     390,   392,   396,   394,   400,   398,   388,     8,     3,     8,
     327,   231,     4,   331,   329,   334,     4,     8,     3,   349,
       4,     4,     8,     3,   260,   262,     3,     8,     4,   437,
     439,     4,   442,     4,     4,   446,   449,     4,     4,     4,
     454,   457,     3,     8,   471,     3,     8,   167,   167,   148,
       4,     4,     4,     4,     4,   186,     4,   151,   151,     4,
       4,     4,     4,     4,   149,   149,   149,   149,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   149,     4,
       4,   192,     4,     4,     4,   151,   202,    77,   182,   230,
     310,   336,   366,   368,   381,   383,   385,   411,   412,   413,
     414,   415,     4,     4,     4,     4,     4,     4,     4,   149,
     151,     4,     4,     4,     4,   282,     4,   363,     4,     4,
       4,     4,     4,     4,     4,     4,   380,     4,     4,   149,
       4,     4,     4,   151,   322,     4,   151,   151,   346,     4,
       4,   258,   151,     4,     4,   149,     4,   149,   149,     4,
       4,   151,   151,   151,     4,     4,   434,     4,   469,     4,
       7,     7,   167,   167,   167,     7,   148,   148,   148,     7,
       7,     5,     5,     5,     5,   169,   171,   167,     5,     5,
       5,     7,     7,     7,     5,   178,    14,    15,   209,    17,
      18,   212,   416,     8,     3,   148,   148,   148,     5,   148,
     148,   148,    72,    73,    74,   299,   148,     5,     7,   148,
     178,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   167,   148,   148,   148,    15,
     117,   447,   118,   119,   120,   121,   122,   151,   455,   148,
       5,   167,   191,   468,   201,    27,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,   182,   218,   219,   220,
     223,   225,   227,   229,   230,   232,   233,   234,   235,   236,
     238,   218,     7,   275,   276,   277,     7,   314,   315,   316,
       7,   338,   339,   340,     7,   304,   305,   306,    80,    81,
      82,    83,    85,   242,   243,   244,   245,   246,   247,   248,
     295,   409,     7,   251,   252,   253,    92,    93,    94,    95,
      96,    97,   265,   266,   267,   268,   269,   270,   271,   272,
      65,   100,   101,   182,   366,   420,   421,   422,   424,   426,
     427,   433,   179,     4,   413,     7,   356,   357,   358,     7,
     372,   373,   374,    87,   405,     7,   472,   473,     8,     8,
       8,   221,   224,   226,   228,     4,     4,     4,     4,     4,
     237,   239,     3,     8,     8,   278,     6,     3,   317,     6,
       3,   341,     6,     3,   307,     6,     3,     3,     6,     3,
       6,   254,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   428,   423,   425,     3,     8,     8,   148,   180,
     181,   148,   359,     6,     3,   375,     6,     3,   406,     8,
     474,     3,     6,     4,     4,     4,     4,   149,   151,   149,
     151,   149,     4,     4,   219,   281,   277,   320,   316,   344,
     340,   182,   193,   194,   195,   198,   230,   273,   291,   295,
     297,   308,   309,   336,   366,   368,   381,   383,   385,   403,
     306,   243,   295,   257,   253,   149,   149,   149,   149,   149,
     149,   266,     4,     4,     4,   421,     6,     3,   362,   358,
     378,   374,     4,   125,   127,   128,   182,   230,   366,   368,
     475,   476,   477,   478,   480,   473,    28,    29,    30,    31,
     222,   148,   148,   148,   148,   148,     8,     8,     8,     3,
       8,     8,   167,   148,   148,   148,     8,     8,   148,   481,
       4,   479,     3,     8,   309,     4,   149,     4,   476,     5,
     148,     7,   482,   483,   484,     3,     6,   126,   129,   130,
     131,   485,   486,   487,   489,   490,   491,   483,   488,     4,
       4,     4,     3,     8,     4,   151,   149,   149,   486,   148
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
     361,   360,   362,   362,   363,   363,   363,   363,   363,   365,
     364,   367,   366,   369,   368,   371,   370,   372,   372,   373,
     373,   375,   374,   377,   376,   378,   378,   379,   379,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   382,   381,   384,   383,   386,   385,
     388,   387,   390,   389,   392,   391,   394,   393,   396,   395,
     398,   397,   400,   399,   402,   401,   404,   403,   406,   405,
     408,   407,   409,   409,   410,   295,   411,   411,   412,   412,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     414,   416,   415,   417,   419,   418,   420,   420,   421,   421,
     421,   421,   421,   423,   422,   425,   424,   426,   428,   427,
     430,   429,   432,   431,   433,   433,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   435,   437,   436,   439,   438,   440,   442,
     441,   443,   444,   446,   445,   447,   447,   449,   448,   450,
     451,   452,   454,   453,   455,   455,   455,   455,   455,   457,
     456,   459,   458,   461,   460,   463,   462,   465,   464,   467,
     466,   468,   468,   469,   471,   470,   472,   472,   474,   473,
     475,   475,   476,   476,   476,   476,   476,   476,   476,   477,
     479,   478,   481,   480,   482,   482,   484,   483,   485,   485,
     486,   486,   486,   486,   488,   487,   489,   490,   491
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
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     1,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
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
  "reservation_client_classes", "$@85", "relay", "$@86", "relay_map",
  "$@87", "client_classes", "$@88", "client_classes_list", "$@89",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@90",
  "dhcp4o6_port", "control_socket", "$@91", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@92",
  "control_socket_name", "$@93", "control_socket_user_context",
  "control_socket_comment", "$@94", "dhcp_ddns", "$@95", "sub_dhcp_ddns",
  "$@96", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@97", "server_ip", "$@98", "server_port",
  "sender_ip", "$@99", "sender_port", "max_queue_size", "ncr_protocol",
  "$@100", "ncr_protocol_value", "ncr_format", "$@101",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@102", "replace_client_name_value",
  "generated_prefix", "$@103", "dhcp6_json_object", "$@104",
  "dhcpddns_json_object", "$@105", "control_agent_json_object", "$@106",
  "logging_object", "$@107", "sub_logging", "$@108", "logging_params",
  "logging_param", "loggers", "$@109", "loggers_entries", "logger_entry",
  "$@110", "logger_params", "logger_param", "debuglevel", "severity",
  "$@111", "output_options_list", "$@112", "output_options_list_content",
  "output_entry", "$@113", "output_params_list", "output_params", "output",
  "$@114", "flush", "maxsize", "maxver", YY_NULLPTR
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
    1331,  1331,  1341,  1342,  1345,  1346,  1347,  1348,  1349,  1352,
    1352,  1360,  1360,  1367,  1367,  1379,  1379,  1389,  1390,  1393,
    1394,  1397,  1397,  1406,  1406,  1415,  1416,  1419,  1420,  1424,
    1425,  1426,  1427,  1428,  1429,  1430,  1431,  1432,  1433,  1434,
    1435,  1436,  1437,  1438,  1441,  1441,  1449,  1449,  1457,  1457,
    1465,  1465,  1473,  1473,  1481,  1481,  1489,  1489,  1497,  1497,
    1505,  1505,  1513,  1513,  1521,  1521,  1534,  1534,  1544,  1544,
    1555,  1555,  1565,  1566,  1569,  1569,  1579,  1580,  1583,  1584,
    1587,  1588,  1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,
    1599,  1601,  1601,  1613,  1620,  1620,  1630,  1631,  1634,  1635,
    1636,  1637,  1638,  1641,  1641,  1649,  1649,  1657,  1659,  1659,
    1668,  1668,  1680,  1680,  1690,  1691,  1694,  1695,  1696,  1697,
    1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,
    1708,  1709,  1710,  1713,  1718,  1718,  1726,  1726,  1734,  1739,
    1739,  1747,  1752,  1757,  1757,  1765,  1766,  1769,  1769,  1777,
    1782,  1787,  1792,  1792,  1800,  1803,  1806,  1809,  1812,  1818,
    1818,  1828,  1828,  1835,  1835,  1842,  1842,  1854,  1854,  1864,
    1864,  1875,  1876,  1880,  1884,  1884,  1896,  1897,  1901,  1901,
    1909,  1910,  1913,  1914,  1915,  1916,  1917,  1918,  1919,  1922,
    1927,  1927,  1935,  1935,  1945,  1946,  1949,  1949,  1957,  1958,
    1961,  1962,  1963,  1964,  1967,  1967,  1975,  1980,  1985
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
#line 4477 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1990 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
