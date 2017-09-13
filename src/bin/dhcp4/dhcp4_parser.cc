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
      case 159: // value
      case 163: // map_value
      case 201: // socket_type
      case 211: // db_type
      case 288: // hr_mode
      case 429: // ncr_protocol_value
      case 437: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 145: // "boolean"
        value.move< bool > (that.value);
        break;

      case 144: // "floating point"
        value.move< double > (that.value);
        break;

      case 143: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 142: // "constant string"
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
      case 159: // value
      case 163: // map_value
      case 201: // socket_type
      case 211: // db_type
      case 288: // hr_mode
      case 429: // ncr_protocol_value
      case 437: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 145: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 144: // "floating point"
        value.copy< double > (that.value);
        break;

      case 143: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 142: // "constant string"
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
            case 142: // "constant string"

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 143: // "integer"

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 144: // "floating point"

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 145: // "boolean"

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 159: // value

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 163: // map_value

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 201: // socket_type

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 211: // db_type

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 288: // hr_mode

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 429: // ncr_protocol_value

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp4_parser.cc" // lalr1.cc:636
        break;

      case 437: // replace_client_name_value

#line 219 "dhcp4_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp4_parser.cc" // lalr1.cc:636
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
      case 159: // value
      case 163: // map_value
      case 201: // socket_type
      case 211: // db_type
      case 288: // hr_mode
      case 429: // ncr_protocol_value
      case 437: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 145: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 144: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 143: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 142: // "constant string"
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
#line 228 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 229 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 230 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP4; }
#line 692 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 231 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 232 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET4; }
#line 704 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 233 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 234 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 716 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 235 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 722 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 236 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 237 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 734 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 238 "dhcp4_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 246 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 746 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 247 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 248 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 249 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 250 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 251 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 776 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 252 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 255 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 791 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 260 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 802 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 265 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 271 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 818 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 278 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 827 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 282 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 289 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 292 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 854 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 300 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 304 "dhcp4_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 872 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 313 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 889 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 322 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 898 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 326 "dhcp4_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 907 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 337 "dhcp4_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 918 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 347 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 929 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 352 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 939 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 373 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 952 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 380 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 964 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 390 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 974 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 394 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 982 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 991 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 433 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1000 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 438 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1009 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 443 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1018 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1027 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 453 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1036 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 459 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1047 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 464 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1056 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 478 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1066 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 482 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1074 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 486 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 491 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 496 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1102 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1111 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 503 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1117 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 504 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1123 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 507 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1132 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 513 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 518 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 523 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1163 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 528 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1172 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 552 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1180 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 554 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1189 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 559 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 560 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 561 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1207 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 562 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 565 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1231 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 573 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1239 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 575 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1249 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 581 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1257 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 583 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 589 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 594 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 596 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1294 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 602 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1303 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 612 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1321 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 617 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1330 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 622 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 624 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1348 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 630 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 632 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1366 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 639 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 644 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1386 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 163:
#line 660 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 164:
#line 665 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 165:
#line 670 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 675 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1422 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 680 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 685 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1442 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 690 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1451 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 174:
#line 703 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1461 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 711 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1479 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 715 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1487 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 183:
#line 728 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1495 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 184:
#line 730 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 736 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1513 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1522 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 744 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1533 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 749 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1542 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 766 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1551 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 771 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1560 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1569 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 781 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1578 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 786 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1587 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1596 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 799 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1607 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1616 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 824 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 828 "dhcp4_parser.yy" // lalr1.cc:859
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
    ctx.stack_.pop_back();
}
#line 1649 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 847 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1659 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 851 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1667 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 883 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 885 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1685 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 891 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 893 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 1703 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 899 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 901 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 1721 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 907 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1729 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 909 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 1739 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 915 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 917 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1757 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 923 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1765 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 925 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1775 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 931 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1783 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 933 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 939 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1801 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 941 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1810 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 946 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1816 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 947 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1822 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 948 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1828 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 951 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1837 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 956 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1846 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1857 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 968 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 262:
#line 983 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1876 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 263:
#line 987 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1884 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1895 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1904 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 285:
#line 1036 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1922 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1047 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1932 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1051 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1077 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1949 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 304:
#line 1084 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1086 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1967 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1092 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1094 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1985 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1100 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1102 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2003 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 311:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 312:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2021 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2030 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2041 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1132 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 321:
#line 1155 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2068 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1162 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2078 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1166 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2086 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1196 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1198 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 340:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2113 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 341:
#line 1213 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2122 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1221 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2133 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1226 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 348:
#line 1241 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2152 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1245 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2160 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2170 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 351:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2178 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 358:
#line 1267 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2186 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 359:
#line 1269 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2196 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 360:
#line 1275 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2204 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1277 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2224 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1290 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2233 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 368:
#line 1303 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2243 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 369:
#line 1307 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2251 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 370:
#line 1311 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2261 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 371:
#line 1315 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2269 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1343 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1345 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1351 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2295 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1353 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2305 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 393:
#line 1359 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 394:
#line 1361 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2323 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 395:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2331 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 396:
#line 1369 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 397:
#line 1375 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2349 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 398:
#line 1377 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2359 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1383 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2367 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1385 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2377 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1391 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1393 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1399 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1401 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2413 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1407 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2421 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2431 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1415 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2439 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2449 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1423 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2460 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1428 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2469 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1436 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2480 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1441 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2489 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1446 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2497 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1448 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2507 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2518 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1462 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2527 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2537 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1475 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2545 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1498 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2553 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2563 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2572 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1517 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2583 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1522 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1537 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2618 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1545 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1553 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2639 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1558 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2648 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1563 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2658 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2666 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1592 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2675 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1597 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1599 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2693 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1605 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2701 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1607 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2711 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2720 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2728 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1620 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2738 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2747 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1631 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2756 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 477:
#line 1636 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2764 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 478:
#line 1638 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2773 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 479:
#line 1644 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2779 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 480:
#line 1645 "dhcp4_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2785 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1648 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2793 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1650 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2803 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1656 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2812 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1661 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2821 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2830 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1671 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2838 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2847 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1679 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2855 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1682 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2863 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1685 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2871 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1688 "dhcp4_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2879 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1691 "dhcp4_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2888 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1697 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2896 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 2906 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1714 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2931 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2940 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1721 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2957 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1738 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2977 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1755 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2997 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1772 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3007 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1776 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1796 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3032 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1798 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3042 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1804 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3053 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1809 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1818 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3072 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1822 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1836 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1838 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3098 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1844 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3107 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3116 "dhcp4_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3125 "dhcp4_parser.cc" // lalr1.cc:859
    break;


#line 3129 "dhcp4_parser.cc" // lalr1.cc:859
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


  const short int Dhcp4Parser::yypact_ninf_ = -678;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short int
  Dhcp4Parser::yypact_[] =
  {
      86,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,    56,    20,    32,    76,    87,   102,   109,   116,
     124,   144,   150,   200,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,    20,   -46,    16,    26,
     273,    13,    99,   106,   118,    50,     7,   235,  -678,   160,
     208,   211,   220,   227,  -678,  -678,  -678,  -678,  -678,   228,
    -678,    33,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   280,
     291,  -678,  -678,  -678,   301,   303,   304,   306,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,   308,  -678,  -678,  -678,
      39,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,   309,    43,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   311,
     312,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
      52,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,    78,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,   247,   261,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,   313,  -678,  -678,  -678,   317,  -678,  -678,
     314,   320,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,   321,   322,  -678,  -678,  -678,  -678,   316,
     324,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,   103,  -678,  -678,  -678,   325,  -678,  -678,   327,  -678,
     328,   344,  -678,  -678,   345,   346,   347,  -678,  -678,  -678,
     114,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,    20,    20,  -678,
     186,   348,   349,   350,   351,   352,  -678,    16,  -678,   353,
     213,   214,   359,   360,   361,   223,   224,   225,   229,   365,
     366,   367,   369,   370,   371,   372,   374,   236,   376,   377,
      26,  -678,   378,   379,   239,   273,  -678,    70,   381,   382,
     383,   384,   385,   386,   387,   252,   253,   388,   389,   390,
     392,    13,  -678,   393,   395,    99,  -678,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,  -678,   106,   406,
     407,   270,   408,   410,   411,   274,  -678,   118,   412,   275,
     276,  -678,    50,   413,   414,   -15,  -678,   277,   419,   420,
     282,   422,   284,   285,   425,   426,   286,   287,   288,   430,
     431,   235,  -678,  -678,  -678,   432,   433,   434,    20,    20,
      20,  -678,   435,  -678,  -678,   295,   437,   438,  -678,  -678,
    -678,  -678,   441,   442,   445,   446,   449,   450,   451,   454,
    -678,   455,   456,  -678,   452,   176,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,   457,   436,  -678,  -678,  -678,
     296,   326,   330,   453,   331,   332,   333,  -678,  -678,    -6,
     334,   459,   462,  -678,   335,   463,  -678,   337,   338,   452,
     339,   340,   341,   342,   343,   354,   355,  -678,   356,   357,
    -678,   358,   362,   363,  -678,  -678,   364,  -678,  -678,  -678,
     368,    20,  -678,  -678,   373,   375,  -678,   380,  -678,  -678,
      35,   394,  -678,  -678,  -678,    88,   391,  -678,    20,    26,
     409,  -678,  -678,  -678,   273,  -678,   164,   164,   480,   481,
     482,   483,   159,    31,   484,   154,   207,   235,  -678,  -678,
    -678,  -678,  -678,   488,  -678,    70,  -678,  -678,  -678,   486,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   487,   418,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,   169,  -678,   206,  -678,
    -678,   226,  -678,  -678,  -678,  -678,   491,   498,   499,   503,
     505,  -678,  -678,  -678,   248,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   249,  -678,
     460,   508,  -678,  -678,   506,   510,  -678,  -678,   512,   511,
    -678,  -678,   513,   517,  -678,  -678,  -678,  -678,  -678,  -678,
      79,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   147,  -678,
     515,   520,  -678,   521,   522,   523,   524,   526,   527,   250,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   251,
    -678,  -678,  -678,   258,   415,   416,  -678,  -678,   518,   529,
    -678,  -678,   528,   532,  -678,  -678,   530,  -678,   533,   409,
    -678,  -678,   535,   536,   537,   538,   417,   421,   424,   423,
     427,   539,   540,   164,  -678,  -678,    13,  -678,   480,   118,
    -678,   481,    50,  -678,   482,    89,  -678,   483,   159,  -678,
      31,  -678,     7,  -678,   484,   428,   429,   439,   440,   443,
     444,   154,  -678,   541,   542,   207,  -678,  -678,  -678,   543,
     544,  -678,    99,  -678,   486,   106,  -678,   487,   546,  -678,
     531,  -678,   265,   447,   448,   458,  -678,  -678,  -678,  -678,
    -678,   461,   464,  -678,   259,  -678,   545,  -678,   547,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   260,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   262,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,   465,   466,  -678,
    -678,   467,   268,  -678,   548,  -678,   468,   509,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,    89,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,   272,  -678,  -678,    -9,   509,  -678,  -678,   550,  -678,
    -678,  -678,   269,  -678,  -678,  -678,  -678,  -678,   555,   469,
     557,    -9,  -678,   558,  -678,   471,  -678,   562,  -678,  -678,
     293,  -678,    54,   562,  -678,  -678,   560,   561,   569,   271,
    -678,  -678,  -678,  -678,  -678,  -678,   570,   470,   473,   474,
      54,  -678,   472,  -678,  -678,  -678,  -678,  -678
  };

  const unsigned short int
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    39,    32,    28,    27,    24,
      25,    26,    31,     3,    29,    30,    52,     5,    64,     7,
     103,     9,   211,    11,   350,    13,   370,    15,   287,    17,
     322,    19,   176,    21,   448,    23,    41,    35,     0,     0,
       0,     0,     0,   372,   289,   324,     0,     0,    43,     0,
      42,     0,     0,    36,    62,   501,   495,   497,   499,     0,
      61,     0,    54,    56,    58,    59,    60,    57,    96,     0,
       0,   389,   112,   114,     0,     0,     0,     0,   203,   279,
     314,   256,   154,   415,   168,   187,     0,   436,   446,    89,
       0,    66,    68,    69,    70,    71,    86,    87,    74,    75,
      76,    77,    81,    82,    72,    73,    79,    80,    88,    78,
      83,    84,    85,   105,   107,     0,     0,    98,   100,   101,
     102,   419,   237,   239,   241,   342,   235,   243,   245,     0,
       0,   249,   247,   362,   411,   234,   215,   216,   217,   229,
       0,   213,   220,   231,   232,   233,   221,   222,   225,   227,
     223,   224,   218,   219,   226,   230,   228,   358,   360,   357,
     355,     0,   352,   354,   356,   391,   393,   409,   397,   399,
     403,   401,   407,   405,   395,   388,   384,     0,   373,   374,
     385,   386,   387,   381,   376,   382,   378,   379,   380,   383,
     377,   304,   144,     0,   308,   306,   311,     0,   300,   301,
       0,   290,   291,   293,   303,   294,   295,   296,   310,   297,
     298,   299,   336,     0,     0,   334,   335,   338,   339,     0,
     325,   326,   328,   329,   330,   331,   332,   333,   183,   185,
     180,     0,   178,   181,   182,     0,   468,   470,     0,   473,
       0,     0,   477,   481,     0,     0,     0,   486,   493,   466,
       0,   450,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,    40,     0,     0,    33,
       0,     0,     0,     0,     0,     0,    51,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,     0,     0,     0,     0,   104,   421,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   212,     0,     0,     0,   351,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,     0,
       0,     0,     0,     0,     0,     0,   288,     0,     0,     0,
       0,   323,     0,     0,     0,     0,   177,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   449,    44,    37,     0,     0,     0,     0,     0,
       0,    55,     0,    94,    95,     0,     0,     0,    90,    91,
      92,    93,     0,     0,     0,     0,     0,     0,     0,     0,
     435,     0,     0,    67,     0,     0,   111,    99,   433,   431,
     432,   427,   428,   429,   430,     0,   422,   423,   425,   426,
       0,     0,     0,     0,     0,     0,     0,   254,   255,     0,
       0,     0,     0,   214,     0,     0,   353,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   375,     0,     0,
     302,     0,     0,     0,   313,   292,     0,   340,   341,   327,
       0,     0,   179,   467,     0,     0,   472,     0,   475,   476,
       0,     0,   483,   484,   485,     0,     0,   451,     0,     0,
       0,   496,   498,   500,     0,   390,     0,     0,   205,   281,
     316,   258,     0,     0,   170,     0,     0,     0,    45,   106,
     109,   110,   108,     0,   420,     0,   238,   240,   242,   344,
     236,   244,   246,   251,   252,   253,   250,   248,   364,     0,
     359,    34,   361,   392,   394,   410,   398,   400,   404,   402,
     408,   406,   396,   305,   145,   309,   307,   312,   337,   184,
     186,   469,   471,   474,   479,   480,   478,   482,   488,   489,
     490,   491,   492,   487,   494,    38,     0,   506,     0,   503,
     505,     0,   131,   137,   139,   141,     0,     0,     0,     0,
       0,   150,   152,   130,     0,   116,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,     0,   209,
       0,   206,   207,   285,     0,   282,   283,   320,     0,   317,
     318,   262,     0,   259,   260,   163,   164,   165,   166,   167,
       0,   156,   158,   159,   160,   161,   162,   417,     0,   174,
       0,   171,   172,     0,     0,     0,     0,     0,     0,     0,
     189,   191,   192,   193,   194,   195,   196,   442,   444,     0,
     438,   440,   441,     0,    47,     0,   424,   348,     0,   345,
     346,   368,     0,   365,   366,   413,     0,    63,     0,     0,
     502,    97,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   115,     0,   204,     0,   289,
     280,     0,   324,   315,     0,     0,   257,     0,     0,   155,
       0,   416,     0,   169,     0,     0,     0,     0,     0,     0,
       0,     0,   188,     0,     0,     0,   437,   447,    49,     0,
      48,   434,     0,   343,     0,   372,   363,     0,     0,   412,
       0,   504,     0,     0,     0,     0,   143,   146,   147,   148,
     149,     0,     0,   117,     0,   208,     0,   284,     0,   319,
     278,   277,   269,   270,   272,   266,   267,   268,   275,     0,
     264,   271,   273,   274,   276,   261,   157,   418,     0,   173,
     197,   198,   199,   200,   201,   202,   190,     0,     0,   439,
      46,     0,     0,   347,     0,   367,     0,     0,   133,   134,
     135,   136,   132,   138,   140,   142,   151,   153,   210,   286,
     321,     0,   263,   175,   443,   445,    50,   349,   369,   414,
     510,     0,   508,   265,     0,     0,   507,   522,     0,   520,
     518,   514,     0,   512,   516,   517,   515,   509,     0,     0,
       0,     0,   511,     0,   519,     0,   513,     0,   521,   526,
       0,   524,     0,     0,   523,   534,     0,     0,     0,     0,
     528,   530,   531,   532,   533,   525,     0,     0,     0,     0,
       0,   527,     0,   536,   537,   538,   529,   535
  };

  const short int
  Dhcp4Parser::yypgoto_[] =
  {
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,   -38,  -678,    93,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,    92,  -678,  -678,  -678,   -58,  -678,
    -678,  -678,   255,  -678,  -678,  -678,  -678,    63,   256,   -60,
     -59,   -44,  -678,  -678,   -40,  -678,  -678,    71,   254,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,    73,  -116,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,   -54,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -130,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -133,  -678,  -678,  -678,
    -128,   210,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -129,
    -678,  -678,  -678,  -678,  -678,  -678,  -677,  -678,  -678,  -678,
    -110,  -678,  -678,  -678,  -105,   257,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -675,  -678,  -678,  -678,  -494,  -678,
    -672,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -114,
    -678,  -678,  -217,  -678,  -678,  -678,  -678,  -106,  -678,  -678,
    -678,  -103,  -678,   230,  -678,   -52,  -678,  -678,  -678,  -678,
    -678,   -42,  -678,  -678,  -678,  -678,  -678,   -47,  -678,  -678,
    -678,  -102,  -678,  -678,  -678,  -101,  -678,   232,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -135,
    -678,  -678,  -678,  -127,   266,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -119,  -678,  -678,  -678,  -115,  -678,   263,
     -39,  -678,  -317,  -678,  -315,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -671,  -678,  -678,  -678,  -670,  -678,  -678,  -678,
    -678,  -678,    94,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -100,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   105,
     233,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,   -56,  -678,  -678,  -678,  -199,  -678,  -678,
    -214,  -678,  -678,  -678,  -678,  -678,  -678,  -225,  -678,  -678,
    -241,  -678,  -678,  -678,  -678,  -678
  };

  const short int
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    32,    33,    34,    57,   542,    72,    73,
      35,    56,    69,    70,   519,   664,   729,   730,   109,    37,
      58,    81,    82,    83,   291,    39,    59,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   299,   136,   137,    41,
      60,   138,   322,   139,   323,   522,   140,   119,   303,   120,
     304,   594,   595,   596,   682,   802,   597,   683,   598,   684,
     599,   685,   600,   219,   360,   602,   603,   604,   605,   606,
     691,   607,   692,   121,   313,   630,   631,   632,   633,   634,
     635,   636,   122,   315,   640,   641,   642,   712,    53,    66,
     251,   252,   253,   373,   254,   374,   123,   316,   649,   650,
     651,   652,   653,   654,   655,   656,   124,   309,   610,   611,
     612,   696,    43,    61,   160,   161,   162,   332,   163,   328,
     164,   329,   165,   330,   166,   333,   167,   334,   168,   338,
     169,   337,   536,   170,   171,   125,   312,   622,   623,   624,
     705,   769,   770,   126,   310,   614,   615,   616,   699,    49,
      64,   220,   221,   222,   223,   224,   225,   226,   359,   227,
     363,   228,   362,   229,   230,   364,   231,   127,   311,   618,
     619,   620,   702,    51,    65,   239,   240,   241,   242,   243,
     368,   244,   245,   246,   247,   173,   331,   668,   669,   670,
     732,    45,    62,   181,   182,   183,   343,   184,   344,   174,
     339,   672,   673,   674,   735,    47,    63,   197,   198,   199,
     128,   302,   201,   347,   202,   348,   203,   356,   204,   350,
     205,   351,   206,   353,   207,   352,   208,   355,   209,   354,
     210,   349,   176,   340,   676,   738,   129,   314,   638,   327,
     435,   436,   437,   438,   439,   523,   130,   131,   318,   659,
     660,   661,   723,   662,   724,   132,   319,    55,    67,   270,
     271,   272,   273,   378,   274,   379,   275,   276,   381,   277,
     278,   279,   384,   566,   280,   385,   281,   282,   283,   284,
     389,   573,   285,   390,    84,   293,    85,   294,    86,   295,
      87,   292,   578,   579,   580,   678,   821,   822,   824,   832,
     833,   834,   835,   840,   836,   838,   850,   851,   852,   859,
     860,   861,   866,   862,   863,   864
  };

  const unsigned short int
  Dhcp4Parser::yytable_[] =
  {
      80,   156,   157,   155,   179,   195,   218,   235,   250,   269,
     433,   236,   434,   237,   172,   180,   196,   158,    68,   637,
     141,   159,   175,   238,   200,    25,    74,    26,   766,    27,
     767,    90,    91,   768,   773,   774,   297,    88,   141,    36,
     212,   298,   320,    89,    90,    91,   325,   321,    92,    93,
     564,   326,    94,    95,    96,   341,    24,   142,   143,   144,
     342,   100,   533,   534,   535,    94,    95,    96,    97,    98,
     248,   249,   145,    99,   100,   146,   147,   148,   149,   150,
     151,   345,   708,    38,   101,   709,   346,   152,   153,    91,
     185,   186,   248,   249,    40,   154,    71,   102,   103,   212,
     232,   213,   214,   233,   234,   152,   375,    90,    91,    42,
     104,   376,   827,   105,   828,   829,    44,   391,   100,   212,
     106,   107,   392,    46,   108,    91,   185,   186,    94,    95,
      96,    48,    98,    79,   766,    75,   767,   100,   212,   768,
     773,   774,   211,   428,    76,    77,    78,   100,   565,    79,
     710,    50,   147,   711,   100,    79,   151,    52,    79,   177,
     178,   103,    28,    29,    30,    31,   286,   212,    79,   213,
     214,   154,   320,   215,   216,   217,   855,   677,   187,   856,
     857,   858,   188,   189,   190,   191,   192,   193,   582,   194,
     520,   521,    79,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   568,   569,   570,   571,    54,   433,   679,
     434,   287,    79,   212,   680,   288,   777,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   289,   325,
     290,    79,   296,   572,   681,   625,   626,   627,   628,    80,
     629,    79,   643,   644,   645,   646,   647,   648,    79,   393,
     394,   693,   693,   721,   725,   357,   694,   695,   722,   726,
      79,   391,   341,   811,   358,   375,   727,   808,   812,   429,
     813,   345,   841,   430,   870,   825,   817,   842,   826,   871,
     431,   156,   157,   155,   300,   133,   134,   179,   432,   135,
     798,   799,   800,   801,   172,   301,   853,   158,   180,   854,
     195,   159,   175,   657,   658,   305,    79,   306,   307,   218,
     308,   196,   317,   324,   235,   335,   336,   361,   236,   200,
     237,   365,   366,   367,   371,   369,   370,   372,   395,   377,
     238,   380,   382,   269,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   383,   386,
     387,   388,   396,   397,   398,   399,   400,   402,   403,   404,
     501,   502,   503,   405,   406,   407,   408,   409,   410,   412,
     413,   414,   411,   415,   416,   417,   418,    79,   419,   420,
     421,   422,   424,   425,   426,   440,   441,   442,   443,   444,
     445,   446,   449,   450,   451,   447,   452,   454,   448,   455,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     468,   469,   471,   470,   472,   473,   476,   480,   481,   474,
     477,   478,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   498,   505,   526,   525,
     499,   500,   504,   560,   506,   507,   508,   509,   593,   593,
     510,   511,   601,   601,   512,   513,   514,   518,   529,   269,
     575,   515,   516,   517,   538,   524,   697,   429,   527,   539,
      26,   430,   528,   530,   531,   532,   537,   540,   431,   543,
     544,   546,   547,   548,   549,   550,   432,   609,   613,   617,
     621,   639,   665,   667,   671,   686,   551,   552,   553,   554,
     555,   675,   687,   688,   556,   557,   558,   689,   567,   690,
     559,   698,   700,   701,   704,   561,   820,   562,   703,   706,
     707,   713,   563,   714,   733,   715,   716,   717,   718,   577,
     719,   720,   734,   574,   736,   737,   797,   740,   739,   742,
     743,   744,   745,   751,   752,   787,   788,   791,   541,   790,
     796,   545,   401,   809,   839,   810,   818,   728,   731,   843,
     746,   845,   576,   847,   867,   868,   747,   748,   749,   849,
     750,   780,   781,   869,   872,   581,   423,   753,   776,   427,
     608,   779,   782,   783,   778,   482,   784,   785,   755,   803,
     804,   754,   786,   775,   823,   757,   756,   475,   453,   793,
     805,   758,   759,   806,   479,   792,   807,   814,   815,   816,
     819,   456,   844,   848,   877,   873,   874,   875,   795,   666,
     794,   467,   663,   741,   497,   789,   837,   846,   865,   876,
       0,     0,     0,     0,     0,   593,   156,   157,   155,   601,
       0,   218,     0,     0,   235,   761,   762,   760,   236,   172,
     237,   765,   158,     0,   250,     0,   159,   175,   771,     0,
     238,   763,     0,     0,     0,   764,   772,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,   195,     0,     0,
       0,     0,     0,     0,     0,   180,     0,     0,   196,     0,
       0,     0,     0,     0,     0,     0,   200,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   761,   762,   760,     0,     0,     0,   765,     0,     0,
       0,     0,     0,     0,   771,     0,   830,   763,     0,     0,
     831,   764,   772,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   830,     0,     0,     0,   831
  };

  const short int
  Dhcp4Parser::yycheck_[] =
  {
      58,    61,    61,    61,    62,    63,    64,    65,    66,    67,
     327,    65,   327,    65,    61,    62,    63,    61,    56,   513,
       7,    61,    61,    65,    63,     5,    10,     7,   705,     9,
     705,    18,    19,   705,   705,   705,     3,    11,     7,     7,
      49,     8,     3,    17,    18,    19,     3,     8,    22,    23,
      15,     8,    39,    40,    41,     3,     0,    44,    45,    46,
       8,    48,    68,    69,    70,    39,    40,    41,    42,    43,
      85,    86,    59,    47,    48,    62,    63,    64,    65,    66,
      67,     3,     3,     7,    58,     6,     8,    74,    75,    19,
      20,    21,    85,    86,     7,    82,   142,    71,    72,    49,
      50,    51,    52,    53,    54,    74,     3,    18,    19,     7,
      84,     8,   121,    87,   123,   124,     7,     3,    48,    49,
      94,    95,     8,     7,    98,    19,    20,    21,    39,    40,
      41,     7,    43,   142,   811,   119,   811,    48,    49,   811,
     811,   811,    24,    73,   128,   129,   130,    48,   113,   142,
       3,     7,    63,     6,    48,   142,    67,     7,   142,    60,
      61,    72,   142,   143,   144,   145,     6,    49,   142,    51,
      52,    82,     3,    55,    56,    57,   122,     8,    72,   125,
     126,   127,    76,    77,    78,    79,    80,    81,    24,    83,
      14,    15,   142,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   115,   116,   117,   118,     7,   525,     3,
     525,     3,   142,    49,     8,     4,   710,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,     8,     3,
       3,   142,     4,   145,     8,    76,    77,    78,    79,   297,
      81,   142,    88,    89,    90,    91,    92,    93,   142,   287,
     288,     3,     3,     3,     3,     8,     8,     8,     8,     8,
     142,     3,     3,     3,     3,     3,     8,     8,     8,   327,
       8,     3,     3,   327,     3,     3,     8,     8,     6,     8,
     327,   341,   341,   341,     4,    12,    13,   345,   327,    16,
      25,    26,    27,    28,   341,     4,     3,   341,   345,     6,
     358,   341,   341,    96,    97,     4,   142,     4,     4,   367,
       4,   358,     4,     4,   372,     4,     4,     4,   372,   358,
     372,     4,     8,     3,     8,     4,     4,     3,   142,     4,
     372,     4,     4,   391,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   145,   145,
     398,   399,   400,     4,     4,     4,   143,   143,   143,     4,
       4,     4,   143,     4,     4,     4,     4,   142,     4,   143,
       4,     4,     4,     4,   145,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   143,     4,     4,   145,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   143,     4,     4,     4,     4,     4,   145,
     145,   145,   145,     4,     4,   143,     4,   143,   143,     4,
       4,   145,   145,   145,     4,     4,     4,   142,   142,     3,
       7,     7,     7,   481,     7,     7,     5,     5,   506,   507,
       5,     5,   506,   507,     5,     5,     5,     5,     5,   517,
     498,     7,     7,     7,     5,     8,     6,   525,   142,     7,
       7,   525,   142,   142,   142,   142,   142,   142,   525,   142,
     142,   142,   142,   142,   142,   142,   525,     7,     7,     7,
       7,     7,     4,     7,     7,     4,   142,   142,   142,   142,
     142,    83,     4,     4,   142,   142,   142,     4,   114,     4,
     142,     3,     6,     3,     3,   142,     7,   142,     6,     6,
       3,     6,   142,     3,     6,     4,     4,     4,     4,   120,
       4,     4,     3,   142,     6,     3,     5,     4,     8,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   455,     6,
       4,   459,   297,     8,     4,     8,     8,   142,   142,     4,
     143,     4,   499,     5,     4,     4,   145,   143,   145,     7,
     143,   143,   143,     4,     4,   504,   320,   693,   708,   325,
     507,   714,   143,   143,   712,   375,   143,   143,   698,   142,
     142,   696,   721,   707,   811,   701,   699,   367,   341,   734,
     142,   702,   704,   142,   372,   732,   142,   142,   142,   142,
     142,   345,   143,   142,   142,   145,   143,   143,   737,   525,
     735,   358,   517,   679,   391,   725,   825,   841,   853,   870,
      -1,    -1,    -1,    -1,    -1,   693,   696,   696,   696,   693,
      -1,   699,    -1,    -1,   702,   705,   705,   705,   702,   696,
     702,   705,   696,    -1,   712,    -1,   696,   696,   705,    -1,
     702,   705,    -1,    -1,    -1,   705,   705,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   732,    -1,    -1,   735,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   732,    -1,    -1,   735,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   735,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   811,   811,   811,    -1,    -1,    -1,   811,    -1,    -1,
      -1,    -1,    -1,    -1,   811,    -1,   824,   811,    -1,    -1,
     824,   811,   811,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   841,    -1,    -1,    -1,   841
  };

  const unsigned short int
  Dhcp4Parser::yystos_[] =
  {
       0,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,     0,     5,     7,     9,   142,   143,
     144,   145,   159,   160,   161,   166,     7,   175,     7,   181,
       7,   195,     7,   268,     7,   347,     7,   361,     7,   305,
       7,   329,     7,   244,     7,   413,   167,   162,   176,   182,
     196,   269,   348,   362,   306,   330,   245,   414,   159,   168,
     169,   142,   164,   165,    10,   119,   128,   129,   130,   142,
     174,   177,   178,   179,   440,   442,   444,   446,    11,    17,
      18,    19,    22,    23,    39,    40,    41,    42,    43,    47,
      48,    58,    71,    72,    84,    87,    94,    95,    98,   174,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   203,
     205,   229,   238,   252,   262,   291,   299,   323,   366,   392,
     402,   403,   411,    12,    13,    16,   193,   194,   197,   199,
     202,     7,    44,    45,    46,    59,    62,    63,    64,    65,
      66,    67,    74,    75,    82,   174,   185,   186,   187,   190,
     270,   271,   272,   274,   276,   278,   280,   282,   284,   286,
     289,   290,   323,   341,   355,   366,   388,    60,    61,   174,
     323,   349,   350,   351,   353,    20,    21,    72,    76,    77,
      78,    79,    80,    81,    83,   174,   323,   363,   364,   365,
     366,   368,   370,   372,   374,   376,   378,   380,   382,   384,
     386,    24,    49,    51,    52,    55,    56,    57,   174,   219,
     307,   308,   309,   310,   311,   312,   313,   315,   317,   319,
     320,   322,    50,    53,    54,   174,   219,   311,   317,   331,
     332,   333,   334,   335,   337,   338,   339,   340,    85,    86,
     174,   246,   247,   248,   250,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   174,
     415,   416,   417,   418,   420,   422,   423,   425,   426,   427,
     430,   432,   433,   434,   435,   438,     6,     3,     4,     8,
       3,   180,   447,   441,   443,   445,     4,     3,     8,   192,
       4,     4,   367,   204,   206,     4,     4,     4,     4,   263,
     300,   324,   292,   230,   393,   239,   253,     4,   404,   412,
       3,     8,   198,   200,     4,     3,     8,   395,   275,   277,
     279,   342,   273,   281,   283,     4,     4,   287,   285,   356,
     389,     3,     8,   352,   354,     3,     8,   369,   371,   387,
     375,   377,   381,   379,   385,   383,   373,     8,     3,   314,
     220,     4,   318,   316,   321,     4,     8,     3,   336,     4,
       4,     8,     3,   249,   251,     3,     8,     4,   419,   421,
       4,   424,     4,     4,   428,   431,     4,     4,     4,   436,
     439,     3,     8,   159,   159,   142,     4,     4,     4,     4,
       4,   178,     4,   145,   145,     4,     4,     4,   143,   143,
     143,   143,     4,     4,     4,     4,     4,     4,     4,     4,
     143,     4,     4,   184,     4,     4,   145,   194,    73,   174,
     219,   323,   366,   368,   370,   396,   397,   398,   399,   400,
       4,     4,     4,     4,     4,     4,     4,   143,   145,     4,
       4,     4,     4,   271,     4,     4,   350,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   365,     4,     4,
     143,     4,     4,     4,   145,   309,     4,   145,   145,   333,
       4,     4,   247,   145,     4,     4,   143,     4,   143,   143,
       4,     4,   145,   145,   145,     4,     4,   416,     4,     7,
       7,   159,   159,   159,     7,   142,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     7,     7,     7,     5,   170,
      14,    15,   201,   401,     8,     3,   142,   142,   142,     5,
     142,   142,   142,    68,    69,    70,   288,   142,     5,     7,
     142,   161,   163,   142,   142,   170,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     159,   142,   142,   142,    15,   113,   429,   114,   115,   116,
     117,   118,   145,   437,   142,   159,   183,   120,   448,   449,
     450,   193,    24,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   174,   207,   208,   209,   212,   214,   216,
     218,   219,   221,   222,   223,   224,   225,   227,   207,     7,
     264,   265,   266,     7,   301,   302,   303,     7,   325,   326,
     327,     7,   293,   294,   295,    76,    77,    78,    79,    81,
     231,   232,   233,   234,   235,   236,   237,   284,   394,     7,
     240,   241,   242,    88,    89,    90,    91,    92,    93,   254,
     255,   256,   257,   258,   259,   260,   261,    96,    97,   405,
     406,   407,   409,   415,   171,     4,   398,     7,   343,   344,
     345,     7,   357,   358,   359,    83,   390,     8,   451,     3,
       8,     8,   210,   213,   215,   217,     4,     4,     4,     4,
       4,   226,   228,     3,     8,     8,   267,     6,     3,   304,
       6,     3,   328,     6,     3,   296,     6,     3,     3,     6,
       3,     6,   243,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   408,   410,     3,     8,     8,   142,   172,
     173,   142,   346,     6,     3,   360,     6,     3,   391,     8,
       4,   449,     4,     4,     4,     4,   143,   145,   143,   145,
     143,     4,     4,   208,   270,   266,   307,   303,   331,   327,
     174,   185,   186,   187,   190,   219,   262,   280,   286,   297,
     298,   323,   366,   388,   392,   295,   232,   284,   246,   242,
     143,   143,   143,   143,   143,   143,   255,     4,     4,   406,
       6,     3,   349,   345,   363,   359,     4,     5,    25,    26,
      27,    28,   211,   142,   142,   142,   142,   142,     8,     8,
       8,     3,     8,     8,   142,   142,   142,     8,     8,   142,
       7,   452,   453,   298,   454,     3,     6,   121,   123,   124,
     174,   219,   455,   456,   457,   458,   460,   453,   461,     4,
     459,     3,     8,     4,   143,     4,   456,     5,   142,     7,
     462,   463,   464,     3,     6,   122,   125,   126,   127,   465,
     466,   467,   469,   470,   471,   463,   468,     4,     4,     4,
       3,     8,     4,   145,   143,   143,   466,   142
  };

  const unsigned short int
  Dhcp4Parser::yyr1_[] =
  {
       0,   146,   148,   147,   149,   147,   150,   147,   151,   147,
     152,   147,   153,   147,   154,   147,   155,   147,   156,   147,
     157,   147,   158,   147,   159,   159,   159,   159,   159,   159,
     159,   160,   162,   161,   163,   164,   164,   165,   165,   167,
     166,   168,   168,   169,   169,   171,   170,   172,   172,   173,
     173,   174,   176,   175,   177,   177,   178,   178,   178,   178,
     178,   178,   180,   179,   182,   181,   183,   183,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     185,   186,   187,   188,   189,   190,   192,   191,   193,   193,
     194,   194,   194,   196,   195,   198,   197,   200,   199,   201,
     201,   202,   204,   203,   206,   205,   207,   207,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   210,   209,   211,   211,   211,   211,   213,   212,   215,
     214,   217,   216,   218,   220,   219,   221,   222,   223,   224,
     226,   225,   228,   227,   230,   229,   231,   231,   232,   232,
     232,   232,   232,   233,   234,   235,   236,   237,   239,   238,
     240,   240,   241,   241,   243,   242,   245,   244,   246,   246,
     246,   247,   247,   249,   248,   251,   250,   253,   252,   254,
     254,   255,   255,   255,   255,   255,   255,   256,   257,   258,
     259,   260,   261,   263,   262,   264,   264,   265,   265,   267,
     266,   269,   268,   270,   270,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   273,   272,   275,   274,   277,
     276,   279,   278,   281,   280,   283,   282,   285,   284,   287,
     286,   288,   288,   288,   289,   290,   292,   291,   293,   293,
     294,   294,   296,   295,   297,   297,   298,   298,   298,   298,
     298,   298,   298,   298,   298,   298,   298,   298,   298,   300,
     299,   301,   301,   302,   302,   304,   303,   306,   305,   307,
     307,   308,   308,   309,   309,   309,   309,   309,   309,   309,
     309,   310,   311,   312,   314,   313,   316,   315,   318,   317,
     319,   321,   320,   322,   324,   323,   325,   325,   326,   326,
     328,   327,   330,   329,   331,   331,   332,   332,   333,   333,
     333,   333,   333,   333,   333,   334,   336,   335,   337,   338,
     339,   340,   342,   341,   343,   343,   344,   344,   346,   345,
     348,   347,   349,   349,   350,   350,   350,   350,   352,   351,
     354,   353,   356,   355,   357,   357,   358,   358,   360,   359,
     362,   361,   363,   363,   364,   364,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   367,
     366,   369,   368,   371,   370,   373,   372,   375,   374,   377,
     376,   379,   378,   381,   380,   383,   382,   385,   384,   387,
     386,   389,   388,   391,   390,   393,   392,   394,   394,   395,
     284,   396,   396,   397,   397,   398,   398,   398,   398,   398,
     398,   398,   399,   401,   400,   402,   404,   403,   405,   405,
     406,   406,   408,   407,   410,   409,   412,   411,   414,   413,
     415,   415,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   417,   419,   418,
     421,   420,   422,   424,   423,   425,   426,   428,   427,   429,
     429,   431,   430,   432,   433,   434,   436,   435,   437,   437,
     437,   437,   437,   439,   438,   441,   440,   443,   442,   445,
     444,   447,   446,   448,   448,   449,   451,   450,   452,   452,
     454,   453,   455,   455,   456,   456,   456,   456,   456,   457,
     459,   458,   461,   460,   462,   462,   464,   463,   465,   465,
     466,   466,   466,   466,   468,   467,   469,   470,   471
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     0,     1,     3,     5,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     1,
       1,     3,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     6,     1,     3,
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
  "\"raw\"", "\"udp\"", "\"re-detect\"", "\"echo-client-id\"",
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
  "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "value", "sub_json", "map2", "$@12", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@13", "list_content",
  "not_empty_list", "list_strings", "$@14", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@15",
  "global_objects", "global_object", "dhcp4_object", "$@16", "sub_dhcp4",
  "$@17", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "decline_probation_period", "echo_client_id",
  "match_client_id", "interfaces_config", "$@18",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@19", "interfaces_list", "$@20", "dhcp_socket_type", "$@21",
  "socket_type", "re_detect", "lease_database", "$@22", "hosts_database",
  "$@23", "database_map_params", "database_map_param", "database_type",
  "$@24", "db_type", "user", "$@25", "password", "$@26", "host", "$@27",
  "port", "name", "$@28", "persist", "lfc_interval", "readonly",
  "connect_timeout", "contact_points", "$@29", "keyspace", "$@30",
  "host_reservation_identifiers", "$@31",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@32", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@33",
  "sub_hooks_library", "$@34", "hooks_params", "hooks_param", "library",
  "$@35", "parameters", "$@36", "expired_leases_processing", "$@37",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@38",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@39",
  "sub_subnet4", "$@40", "subnet4_params", "subnet4_param", "subnet",
  "$@41", "subnet_4o6_interface", "$@42", "subnet_4o6_interface_id",
  "$@43", "subnet_4o6_subnet", "$@44", "interface", "$@45", "interface_id",
  "$@46", "client_class", "$@47", "reservation_mode", "$@48", "hr_mode",
  "id", "rapid_commit", "shared_networks", "$@49",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@50", "shared_network_params", "shared_network_param",
  "option_def_list", "$@51", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@52",
  "sub_option_def", "$@53", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@54",
  "option_def_record_types", "$@55", "space", "$@56", "option_def_space",
  "option_def_encapsulate", "$@57", "option_def_array", "option_data_list",
  "$@58", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@59", "sub_option_data", "$@60",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@61",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@62", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@63", "sub_pool4", "$@64",
  "pool_params", "pool_param", "pool_entry", "$@65", "user_context",
  "$@66", "reservations", "$@67", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@68", "sub_reservation",
  "$@69", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@70", "server_hostname", "$@71",
  "boot_file_name", "$@72", "ip_address", "$@73", "duid", "$@74",
  "hw_address", "$@75", "client_id_value", "$@76", "circuit_id_value",
  "$@77", "flex_id_value", "$@78", "hostname", "$@79",
  "reservation_client_classes", "$@80", "relay", "$@81", "relay_map",
  "$@82", "client_classes", "$@83", "client_classes_list", "$@84",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@85",
  "dhcp4o6_port", "control_socket", "$@86", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@87",
  "control_socket_name", "$@88", "dhcp_ddns", "$@89", "sub_dhcp_ddns",
  "$@90", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@91", "server_ip", "$@92", "server_port",
  "sender_ip", "$@93", "sender_port", "max_queue_size", "ncr_protocol",
  "$@94", "ncr_protocol_value", "ncr_format", "$@95",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@96", "replace_client_name_value",
  "generated_prefix", "$@97", "dhcp6_json_object", "$@98",
  "dhcpddns_json_object", "$@99", "control_agent_json_object", "$@100",
  "logging_object", "$@101", "logging_params", "logging_param", "loggers",
  "$@102", "loggers_entries", "logger_entry", "$@103", "logger_params",
  "logger_param", "debuglevel", "severity", "$@104", "output_options_list",
  "$@105", "output_options_list_content", "output_entry", "$@106",
  "output_params_list", "output_params", "output", "$@107", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short int
  Dhcp4Parser::yyrline_[] =
  {
       0,   228,   228,   228,   229,   229,   230,   230,   231,   231,
     232,   232,   233,   233,   234,   234,   235,   235,   236,   236,
     237,   237,   238,   238,   246,   247,   248,   249,   250,   251,
     252,   255,   260,   260,   271,   274,   275,   278,   282,   289,
     289,   296,   297,   300,   304,   311,   311,   318,   319,   322,
     326,   337,   347,   347,   360,   361,   365,   366,   367,   368,
     369,   370,   373,   373,   390,   390,   398,   399,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     428,   433,   438,   443,   448,   453,   459,   459,   469,   470,
     473,   474,   475,   478,   478,   486,   486,   496,   496,   503,
     504,   507,   513,   513,   523,   523,   533,   534,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   552,   552,   559,   560,   561,   562,   565,   565,   573,
     573,   581,   581,   589,   594,   594,   602,   607,   612,   617,
     622,   622,   630,   630,   639,   639,   649,   650,   653,   654,
     655,   656,   657,   660,   665,   670,   675,   680,   685,   685,
     695,   696,   699,   700,   703,   703,   711,   711,   719,   720,
     721,   724,   725,   728,   728,   736,   736,   744,   744,   754,
     755,   758,   759,   760,   761,   762,   763,   766,   771,   776,
     781,   786,   791,   799,   799,   812,   813,   816,   817,   824,
     824,   847,   847,   856,   857,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   873,   874,   875,
     876,   877,   878,   879,   880,   883,   883,   891,   891,   899,
     899,   907,   907,   915,   915,   923,   923,   931,   931,   939,
     939,   946,   947,   948,   951,   956,   963,   963,   974,   975,
     979,   980,   983,   983,   991,   992,   995,   996,   997,   998,
     999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1014,
    1014,  1026,  1027,  1030,  1031,  1036,  1036,  1047,  1047,  1057,
    1058,  1061,  1062,  1065,  1066,  1067,  1068,  1069,  1070,  1071,
    1072,  1075,  1077,  1082,  1084,  1084,  1092,  1092,  1100,  1100,
    1108,  1110,  1110,  1118,  1127,  1127,  1139,  1140,  1145,  1146,
    1151,  1151,  1162,  1162,  1173,  1174,  1179,  1180,  1185,  1186,
    1187,  1188,  1189,  1190,  1191,  1194,  1196,  1196,  1204,  1206,
    1208,  1213,  1221,  1221,  1233,  1234,  1237,  1238,  1241,  1241,
    1249,  1249,  1257,  1258,  1261,  1262,  1263,  1264,  1267,  1267,
    1275,  1275,  1285,  1285,  1295,  1296,  1299,  1300,  1303,  1303,
    1311,  1311,  1319,  1320,  1323,  1324,  1328,  1329,  1330,  1331,
    1332,  1333,  1334,  1335,  1336,  1337,  1338,  1339,  1340,  1343,
    1343,  1351,  1351,  1359,  1359,  1367,  1367,  1375,  1375,  1383,
    1383,  1391,  1391,  1399,  1399,  1407,  1407,  1415,  1415,  1423,
    1423,  1436,  1436,  1446,  1446,  1457,  1457,  1467,  1468,  1471,
    1471,  1479,  1480,  1483,  1484,  1487,  1488,  1489,  1490,  1491,
    1492,  1493,  1496,  1498,  1498,  1510,  1517,  1517,  1527,  1528,
    1531,  1532,  1535,  1535,  1543,  1543,  1553,  1553,  1563,  1563,
    1571,  1572,  1575,  1576,  1577,  1578,  1579,  1580,  1581,  1582,
    1583,  1584,  1585,  1586,  1587,  1588,  1589,  1592,  1597,  1597,
    1605,  1605,  1613,  1618,  1618,  1626,  1631,  1636,  1636,  1644,
    1645,  1648,  1648,  1656,  1661,  1666,  1671,  1671,  1679,  1682,
    1685,  1688,  1691,  1697,  1697,  1707,  1707,  1714,  1714,  1721,
    1721,  1733,  1733,  1746,  1747,  1751,  1755,  1755,  1767,  1768,
    1772,  1772,  1780,  1781,  1784,  1785,  1786,  1787,  1788,  1791,
    1796,  1796,  1804,  1804,  1814,  1815,  1818,  1818,  1826,  1827,
    1830,  1831,  1832,  1833,  1836,  1836,  1844,  1849,  1854
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
#line 4250 "dhcp4_parser.cc" // lalr1.cc:1167
#line 1859 "dhcp4_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
