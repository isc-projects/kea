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
#define yylex   parser6_lex

// First part of user declarations.

#line 39 "dhcp6_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "dhcp6_parser.h"

// User implementation prologue.

#line 53 "dhcp6_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:413

#include <dhcp6/parser_context.h>

#line 59 "dhcp6_parser.cc" // lalr1.cc:413


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:479
namespace isc { namespace dhcp {
#line 145 "dhcp6_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 173: // value
      case 177: // map_value
      case 221: // db_type
      case 297: // hr_mode
      case 430: // duid_type
      case 466: // ncr_protocol_value
      case 474: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 156: // "boolean"
        value.move< bool > (that.value);
        break;

      case 155: // "floating point"
        value.move< double > (that.value);
        break;

      case 154: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 153: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 173: // value
      case 177: // map_value
      case 221: // db_type
      case 297: // hr_mode
      case 430: // duid_type
      case 466: // ncr_protocol_value
      case 474: // replace_client_name_value
        value.copy< ElementPtr > (that.value);
        break;

      case 156: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 155: // "floating point"
        value.copy< double > (that.value);
        break;

      case 154: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 153: // "constant string"
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
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
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
            case 153: // "constant string"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 154: // "integer"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 155: // "floating point"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 156: // "boolean"

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 173: // value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 177: // map_value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 221: // db_type

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 297: // hr_mode

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 430: // duid_type

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 466: // ncr_protocol_value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 474: // replace_client_name_value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Dhcp6Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Dhcp6Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  inline Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::parse ()
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
      case 173: // value
      case 177: // map_value
      case 221: // db_type
      case 297: // hr_mode
      case 430: // duid_type
      case 466: // ncr_protocol_value
      case 474: // replace_client_name_value
        yylhs.value.build< ElementPtr > ();
        break;

      case 156: // "boolean"
        yylhs.value.build< bool > ();
        break;

      case 155: // "floating point"
        yylhs.value.build< double > ();
        break;

      case 154: // "integer"
        yylhs.value.build< int64_t > ();
        break;

      case 153: // "constant string"
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
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 247 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 248 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 249 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 250 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 251 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.LOGGING; }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 261 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 262 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 264 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 794 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 265 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 800 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 809 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 820 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 830 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 284 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 836 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 291 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 295 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 855 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 302 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 864 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 872 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 313 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 317 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 890 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 324 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 898 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 326 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 907 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 335 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 916 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 339 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 925 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 350 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 936 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 947 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 388 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 973 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 395 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 407 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No global parameter is required
    // parsing completed
}
#line 1002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 450 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 460 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1038 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 465 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1047 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 470 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1068 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 485 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 501 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 506 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 517 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 522 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 534 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 560 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 562 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1177 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 567 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 568 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 569 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1195 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 570 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 575 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1227 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 583 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 589 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 591 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1264 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 604 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 610 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 153:
#line 615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 154:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 155:
#line 625 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1318 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 156:
#line 630 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 638 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 640 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1365 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 161:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1374 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 665 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 670 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 675 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 680 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 175:
#line 694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 699 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 706 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 711 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1461 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 180:
#line 721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 738 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1490 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 748 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 194:
#line 763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 195:
#line 765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1528 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 196:
#line 771 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 197:
#line 773 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 198:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1556 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1566 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 208:
#line 802 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1575 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 209:
#line 807 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1584 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 210:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1593 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 827 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1620 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 215:
#line 840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 220:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 221:
#line 864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1676 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 222:
#line 886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 223:
#line 890 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 923 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 931 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 939 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1750 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 251:
#line 947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 252:
#line 949 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 253:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 254:
#line 957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1785 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 962 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 963 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 257:
#line 964 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1803 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 258:
#line 967 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1812 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 259:
#line 972 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 260:
#line 980 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1832 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 261:
#line 985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 266:
#line 1000 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 267:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 286:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1870 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 287:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 288:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1888 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 289:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 294:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1906 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 295:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 297:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1940 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 313:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1126 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 318:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1985 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 319:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 320:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 322:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 323:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 324:
#line 1158 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2030 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 325:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 326:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2060 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 332:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2069 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 333:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2079 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2088 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 349:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 350:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2106 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 361:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2154 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2174 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 372:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 373:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2201 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 374:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 375:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2218 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1330 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
    e->set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.stack_.back()->combine_set("user-context", e);
    ctx.leave();
}
#line 2237 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2248 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1347 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2257 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2267 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1366 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2279 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2328 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1414 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2355 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2384 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2394 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2403 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2433 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2442 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2453 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2462 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2545 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1558 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2565 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2574 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2622 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1621 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2661 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2672 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2689 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2695 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2701 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1668 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2707 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2743 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2772 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->combine_set("comment", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1756 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2856 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1763 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2866 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2876 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2911 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1824 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1840 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2974 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2983 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2989 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3003 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3022 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3040 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1875 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3057 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3065 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3081 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3089 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3098 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3106 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3124 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3133 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1918 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3150 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3167 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 566:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 567:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3197 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 568:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3205 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 572:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3216 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1973 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 576:
#line 1985 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 577:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3243 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2006 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3260 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 589:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3270 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 590:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3281 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3290 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 594:
#line 2033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3300 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 595:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3308 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3326 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 604:
#line 2059 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3335 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 605:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 606:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3353 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3357 "dhcp6_parser.cc" // lalr1.cc:859
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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int Dhcp6Parser::yypact_ninf_ = -764;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     315,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,    42,    26,    41,    60,    89,
      91,   112,   118,   139,   143,   152,   157,   159,   171,   182,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,    26,  -109,
      33,   186,    34,    49,    46,    -2,   206,    57,   149,   208,
     -27,   437,    29,  -764,   235,   234,   254,   259,   271,  -764,
    -764,  -764,  -764,  -764,   276,  -764,    37,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,   285,   286,   295,   307,
     312,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,   320,  -764,  -764,  -764,    61,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,   331,  -764,    67,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,   334,
     336,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
      85,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,   128,
    -764,  -764,  -764,  -764,  -764,   337,  -764,   340,   342,  -764,
    -764,  -764,  -764,   132,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,   344,   351,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,   350,  -764,  -764,   358,  -764,  -764,  -764,   360,  -764,
    -764,   357,   364,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,   366,   367,  -764,  -764,
    -764,  -764,   376,   371,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,   140,  -764,  -764,  -764,
     382,  -764,  -764,   389,  -764,   390,   392,  -764,  -764,   393,
     394,   396,  -764,  -764,  -764,  -764,  -764,   144,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,   146,  -764,  -764,  -764,    26,    26,
    -764,   249,   399,   412,   413,   414,   415,  -764,    33,  -764,
     416,   417,   418,   221,   272,   273,   274,   275,   421,   426,
     430,   431,   432,   433,   434,   435,   436,   438,   439,   440,
     441,   287,   442,   444,   186,  -764,   445,   313,    34,  -764,
     154,   447,   464,   466,   467,   468,   319,   323,   471,   472,
     473,   474,    49,  -764,   476,    46,  -764,   477,   329,   478,
     330,   335,    -2,  -764,   484,   488,   491,   492,   493,   494,
     495,  -764,   206,  -764,   496,   500,   353,   501,   505,   506,
     355,  -764,   149,   509,   361,   362,  -764,   208,   510,   512,
       1,  -764,   365,   515,   516,   372,   521,   373,   374,   526,
     527,   377,   379,   380,   528,   533,   437,  -764,   535,    29,
    -764,  -764,  -764,   536,   534,   550,    26,    26,    26,  -764,
     552,   554,   555,  -764,  -764,  -764,  -764,  -764,   558,   559,
     561,   560,    26,   563,   564,   565,   566,   567,   568,   569,
     570,  -764,   571,   572,  -764,   575,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,   574,   580,  -764,  -764,  -764,   579,
     581,   422,   443,   446,  -764,  -764,   284,   448,   582,   578,
    -764,   449,  -764,   450,  -764,   451,  -764,  -764,  -764,   575,
     575,   575,   452,   453,   454,   455,  -764,   456,   457,  -764,
     458,   459,   460,  -764,  -764,   461,  -764,  -764,  -764,   462,
      26,  -764,  -764,   463,   465,  -764,   469,  -764,  -764,    87,
     470,  -764,  -764,  -764,   -52,   475,  -764,   583,  -764,    26,
     186,    29,  -764,  -764,  -764,    34,   385,   385,   584,   586,
     587,  -764,  -764,  -764,   588,   -36,    26,   240,    27,   590,
     205,    76,   156,   437,  -764,  -764,   585,  -764,   154,   591,
     593,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,   610,
     537,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,   613,  -764,   150,   153,   169,  -764,  -764,
    -764,  -764,   617,   619,   620,   621,   622,  -764,  -764,  -764,
     195,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,   201,  -764,   623,   624,  -764,  -764,
     625,   627,  -764,  -764,   626,   630,  -764,  -764,   628,   632,
    -764,  -764,  -764,   131,  -764,  -764,  -764,   631,  -764,  -764,
    -764,   222,  -764,  -764,  -764,  -764,   322,  -764,   633,   635,
    -764,   636,   637,   638,   639,   640,   641,   224,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,   642,   643,   644,
    -764,  -764,  -764,  -764,   228,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,   231,  -764,  -764,  -764,
    -764,  -764,   237,   483,   497,  -764,  -764,   645,   646,  -764,
    -764,   647,   649,  -764,  -764,   648,   652,  -764,  -764,   650,
    -764,   324,  -764,  -764,  -764,  -764,   653,   655,   656,   657,
     420,   507,   502,   508,   511,   658,   662,   385,  -764,  -764,
      49,  -764,   584,   149,  -764,   586,   208,  -764,   587,    82,
    -764,   588,   -36,  -764,  -764,   240,  -764,    27,  -764,   -27,
    -764,   590,   513,   514,   517,   518,   519,   520,   205,  -764,
     665,   666,   522,   523,   524,    76,  -764,   671,   675,   676,
     156,  -764,  -764,  -764,   677,   678,  -764,    46,  -764,   591,
      -2,  -764,   593,   206,  -764,   610,   680,  -764,   321,   613,
    -764,   363,   529,   532,   538,  -764,  -764,  -764,  -764,  -764,
     539,   540,  -764,   258,  -764,   679,  -764,   681,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,   267,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,   268,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
     120,   541,  -764,  -764,  -764,  -764,    26,   542,   543,  -764,
    -764,   545,   270,  -764,   298,  -764,   682,  -764,   546,  -764,
     684,  -764,  -764,  -764,  -764,  -764,   300,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,    82,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,   698,   551,   703,   321,  -764,  -764,   707,  -764,   576,
    -764,   701,  -764,  -764,   328,  -764,    -6,   701,  -764,  -764,
     712,   714,   718,   302,  -764,  -764,  -764,  -764,  -764,  -764,
     724,   530,   577,   589,    -6,  -764,   592,  -764,  -764,  -764,
    -764,  -764
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   106,     9,   222,    11,
     363,    13,   386,    15,   414,    17,   288,    19,   296,    21,
     333,    23,   187,    25,   510,    27,   567,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   416,     0,   298,   335,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     565,   559,   561,   563,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   104,   118,   120,     0,     0,     0,     0,
       0,   214,   286,   325,   374,   376,   260,   160,   177,   168,
     449,   179,   198,   468,     0,   492,   508,    98,     0,    72,
      74,    75,    76,    77,    78,    81,    82,    83,    84,    86,
      85,    90,    91,    79,    80,    88,    89,    96,    97,    87,
      92,    93,    94,    95,   115,     0,   114,     0,   108,   110,
     111,   112,   113,   453,   355,   378,   245,   247,   249,     0,
       0,   253,   251,   406,   445,   244,   226,   227,   228,   229,
       0,   224,   233,   234,   235,   238,   240,   236,   237,   230,
     231,   242,   243,   232,   239,   241,   372,   371,   368,     0,
     365,   367,   369,   370,   399,     0,   402,     0,     0,   398,
     393,   396,   397,     0,   388,   390,   391,   394,   395,   392,
     443,   431,   433,   435,   437,   439,   441,   430,   427,   428,
     429,     0,   417,   418,   422,   423,   420,   424,   425,   426,
     421,     0,   315,   150,     0,   319,   317,   322,     0,   311,
     312,     0,   299,   300,   302,   314,   303,   304,   305,   321,
     306,   307,   308,   309,   310,   349,     0,     0,   347,   348,
     351,   352,     0,   336,   337,   339,   340,   341,   342,   343,
     344,   345,   346,   194,   196,   191,     0,   189,   192,   193,
       0,   532,   534,     0,   537,     0,     0,   541,   545,     0,
       0,     0,   550,   557,   530,   528,   529,     0,   512,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   572,     0,   569,   571,    46,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    57,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,     0,   107,
     455,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,     0,     0,   364,     0,     0,     0,
       0,     0,     0,   387,     0,     0,     0,     0,     0,     0,
       0,   415,     0,   289,     0,     0,     0,     0,     0,     0,
       0,   297,     0,     0,     0,     0,   334,     0,     0,     0,
       0,   188,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   511,     0,     0,
     568,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   491,     0,     0,    73,     0,   117,   109,   466,   464,
     465,   461,   462,   463,     0,   456,   457,   459,   460,     0,
       0,     0,     0,     0,   258,   259,     0,     0,     0,     0,
     225,     0,   366,     0,   401,     0,   404,   405,   389,     0,
       0,     0,     0,     0,     0,     0,   419,     0,     0,   313,
       0,     0,     0,   324,   301,     0,   353,   354,   338,     0,
       0,   190,   531,     0,     0,   536,     0,   539,   540,     0,
       0,   547,   548,   549,     0,     0,   513,     0,   570,     0,
       0,     0,   560,   562,   564,     0,     0,     0,   216,   290,
     327,    40,   375,   377,   262,     0,    47,     0,     0,   181,
       0,     0,     0,     0,    51,   116,     0,   454,     0,   357,
     380,   246,   248,   250,   255,   256,   257,   254,   252,   408,
       0,   373,   400,   403,   444,   432,   434,   436,   438,   440,
     442,   316,   151,   320,   318,   323,   350,   195,   197,   533,
     535,   538,   543,   544,   542,   546,   552,   553,   554,   555,
     556,   551,   558,     0,    44,     0,     0,     0,   137,   143,
     145,   147,     0,     0,     0,     0,     0,   156,   158,   136,
       0,   122,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,     0,   220,     0,   217,   218,   294,
       0,   291,   292,   331,     0,   328,   329,   266,     0,   263,
     264,   166,   167,     0,   162,   164,   165,     0,   175,   176,
     172,     0,   170,   173,   174,   451,     0,   185,     0,   182,
     183,     0,     0,     0,     0,     0,     0,     0,   200,   202,
     203,   204,   205,   206,   207,   481,   487,     0,     0,     0,
     480,   477,   478,   479,     0,   470,   472,   475,   473,   474,
     476,   506,   501,   503,   500,   505,     0,   494,   496,   497,
     498,   499,     0,    53,     0,   458,   361,     0,   358,   359,
     384,     0,   381,   382,   412,     0,   409,   410,   447,     0,
     576,     0,   574,    69,   566,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   121,
       0,   215,     0,   298,   287,     0,   335,   326,     0,     0,
     261,     0,     0,   161,   178,     0,   169,     0,   450,     0,
     180,     0,     0,     0,     0,     0,     0,     0,     0,   199,
       0,     0,     0,     0,     0,     0,   469,     0,     0,     0,
       0,   493,   509,    55,     0,    54,   467,     0,   356,     0,
       0,   379,     0,   416,   407,     0,     0,   446,     0,     0,
     573,     0,     0,     0,     0,   149,   152,   153,   154,   155,
       0,     0,   123,     0,   219,     0,   293,     0,   330,   285,
     280,   282,   274,   275,   270,   271,   272,   273,   279,   278,
     281,     0,   268,   276,   283,   284,   277,   265,   163,   171,
     452,     0,   184,   208,   209,   210,   211,   212,   213,   201,
       0,     0,   486,   489,   490,   471,     0,     0,     0,   495,
      52,     0,     0,   360,     0,   383,     0,   411,     0,   590,
       0,   588,   586,   580,   584,   585,     0,   578,   582,   583,
     581,   575,   139,   140,   141,   142,   138,   144,   146,   148,
     157,   159,   221,   295,   332,     0,   267,   186,   483,   484,
     485,   482,   488,   507,   502,   504,    56,   362,   385,   413,
     448,     0,     0,     0,     0,   577,   269,     0,   587,     0,
     579,     0,   589,   594,     0,   592,     0,     0,   591,   602,
       0,     0,     0,     0,   596,   598,   599,   600,   601,   593,
       0,     0,     0,     0,     0,   595,     0,   604,   605,   606,
     597,   603
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,   -15,  -764,   277,  -764,
    -764,  -764,  -764,  -764,  -764,   166,  -764,  -119,  -764,  -764,
    -764,   -70,  -764,  -764,  -764,   395,  -764,  -764,  -764,  -764,
     187,   375,   -59,   -56,   -53,   -45,  -764,  -764,  -764,  -764,
    -764,   181,   378,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
     184,   -25,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,   -66,  -764,  -559,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,   -38,  -552,  -764,  -764,  -764,
    -764,   -37,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
     -42,  -764,  -764,  -764,   -35,   332,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,   -47,  -764,  -764,  -764,  -764,  -764,  -764,
    -763,  -764,  -764,  -764,   -17,  -764,  -764,  -764,   -11,   383,
    -764,  -764,  -758,  -764,  -757,  -764,  -549,  -764,  -742,  -764,
    -764,  -764,  -741,  -764,  -764,  -764,  -764,   -14,  -764,  -764,
    -161,   692,  -764,  -764,  -764,  -764,  -764,    -5,  -764,  -764,
    -764,    -1,  -764,   368,  -764,   -72,  -764,  -764,  -764,  -764,
    -764,   -61,  -764,  -764,  -764,  -764,  -764,     3,  -764,  -764,
    -764,    -3,  -764,  -764,  -764,     0,  -764,   369,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,   -41,
    -764,  -764,  -764,   -40,   398,  -764,  -764,   -49,  -764,   -13,
    -764,  -764,  -764,  -764,  -764,   -34,  -764,  -764,  -764,   -39,
     397,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,   -32,  -764,  -764,  -764,   -33,  -764,   400,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -740,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,   207,  -764,  -764,  -764,  -764,  -764,  -764,
     -21,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,   -23,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,   218,   359,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
    -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,  -764,
     243,   370,  -764,  -764,  -764,   -31,  -764,  -764,  -148,  -764,
    -764,  -764,  -764,  -764,  -764,  -160,  -764,  -764,  -175,  -764,
    -764,  -764,  -764,  -764
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     562,    87,    88,    41,    68,    84,    85,   575,   733,   814,
     815,   127,    43,    70,    96,    97,    98,   332,    45,    71,
     128,   129,   130,   131,   132,   133,   134,   135,   340,    47,
      72,   157,   158,   159,   366,   160,   136,   341,   137,   342,
     640,   641,   642,   756,   916,   643,   757,   644,   758,   645,
     759,   646,   250,   405,   648,   649,   650,   651,   652,   765,
     653,   766,   138,   354,   673,   674,   675,   676,   139,   356,
     681,   682,   683,   684,   140,   355,   141,   358,   688,   689,
     690,   789,    63,    80,   286,   287,   288,   418,   289,   419,
     142,   359,   697,   698,   699,   700,   701,   702,   703,   704,
     143,   348,   656,   657,   658,   770,    49,    73,   180,   181,
     182,   373,   183,   374,   184,   375,   185,   379,   186,   378,
     587,   187,   188,   144,   353,   668,   669,   670,   779,   861,
     862,   145,   349,    57,    77,   660,   661,   662,   773,    59,
      78,   251,   252,   253,   254,   255,   256,   257,   404,   258,
     408,   259,   407,   260,   261,   409,   262,   146,   350,   664,
     665,   666,   776,    61,    79,   272,   273,   274,   275,   276,
     413,   277,   278,   279,   280,   190,   371,   737,   738,   739,
     817,    51,    74,   199,   200,   201,   384,   147,   351,   148,
     352,   193,   372,   741,   742,   743,   820,    53,    75,   213,
     214,   215,   387,   216,   217,   389,   218,   219,   194,   380,
     745,   746,   747,   823,    55,    76,   231,   232,   233,   234,
     395,   235,   396,   236,   397,   237,   398,   238,   399,   239,
     400,   240,   394,   195,   381,   749,   826,   149,   357,   686,
     370,   484,   485,   486,   487,   488,   576,   150,   360,   714,
     715,   716,   800,   931,   717,   718,   801,   719,   720,   151,
     152,   362,   726,   727,   728,   808,   729,   809,   730,   731,
     807,   153,   363,    65,    81,   307,   308,   309,   310,   423,
     311,   424,   312,   313,   426,   314,   315,   316,   429,   614,
     317,   430,   318,   319,   320,   321,   434,   621,   322,   435,
      99,   334,   100,   335,   101,   336,   102,   333,    67,    82,
     324,   325,   326,   438,   751,   752,   828,   906,   907,   908,
     909,   943,   910,   941,   954,   955,   956,   963,   964,   965,
     970,   966,   967,   968
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,    38,   156,   175,   197,   209,   227,   270,   249,   268,
     285,   304,   711,   269,   176,   680,   855,   177,   271,   685,
     178,   856,   857,   161,   191,   202,   211,   229,   179,   263,
     281,    31,   305,    32,   163,    33,   113,   859,   860,   866,
     338,   671,    30,    89,    86,   339,   154,   155,    42,   204,
     205,   206,   207,   208,   114,   115,   163,   283,   284,   162,
     192,   203,   212,   230,   364,   264,   282,    44,   306,   365,
     368,   616,   617,   618,   619,   369,   189,   198,   210,   228,
     106,   107,   108,   109,   113,   283,   284,   113,   382,   163,
     114,   115,   705,   383,   112,   196,    46,   164,    48,   165,
     172,   633,   114,   115,   620,   114,   115,   166,   167,   168,
     169,   170,   171,   106,   107,   108,   109,   672,   111,    50,
     113,   243,   172,   173,   959,    52,    94,   960,   961,   962,
     174,   385,   114,   115,   782,   392,   386,   783,   114,   115,
     393,   167,   168,   420,   170,   171,    54,   436,   421,   439,
      56,    94,   437,   364,   440,   172,   439,   323,   753,    58,
      90,   754,   855,   174,    60,   242,    62,   856,   857,    91,
      92,    93,   368,   706,   707,   708,   709,   755,    64,    34,
      35,    36,    37,   859,   860,   866,    94,    94,   243,    66,
     244,   245,   113,   243,   246,   247,   248,   103,   767,    94,
     104,   105,    94,   768,   767,   114,   115,   612,   613,   769,
     114,   115,   114,   721,   928,   929,   930,   106,   107,   108,
     109,   110,   111,   112,   113,   785,   478,   798,   786,    94,
     858,   805,   799,   680,   810,    94,   806,   328,   870,   811,
     436,   327,   114,   115,   113,   812,   711,   243,   265,   244,
     245,   266,   267,   116,   117,   118,   119,   120,   329,   722,
     723,   382,   114,   115,   114,   115,   922,   330,    95,   121,
     925,   420,   122,   385,   331,   926,   927,   220,   937,   123,
     337,   221,   222,   223,   224,   225,   226,   124,   125,   343,
     344,   126,   691,   692,   693,   694,   695,   696,   156,   345,
     479,   392,    94,   944,   480,   974,   938,    94,   945,    94,
     975,   346,   175,   441,   442,   197,   347,   671,   678,   161,
     679,   482,   209,   176,   361,   787,   177,   829,   788,   178,
     830,   957,   227,   191,   958,   367,   202,   179,   376,    94,
     377,   388,   249,   211,   390,   270,   391,   268,   584,   585,
     586,   269,   401,   229,   402,   162,   271,   483,   403,    94,
     243,    94,   406,   263,   410,   411,   304,   412,   281,   192,
     414,   415,   203,   481,   417,   453,   858,   114,   115,   212,
     912,   913,   914,   915,   416,   189,   422,   305,   198,   230,
     594,   595,   596,   425,   427,   210,   428,   431,   432,   264,
     433,   628,   443,   444,   282,   228,   629,   630,   631,   632,
     633,   634,   635,   636,   637,   638,   445,   446,   447,   448,
     450,   451,   452,   306,   243,   458,   454,   455,   456,   457,
     459,   552,   553,   554,   460,   461,   462,   463,   464,   465,
     466,   471,   467,   468,   469,   470,   472,   563,   473,   475,
     899,   489,   900,   901,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   490,   476,
     491,   492,   493,   494,    94,   496,   497,   498,   499,   495,
     501,   503,   505,   504,   506,   156,   639,   639,   509,   507,
     647,   647,   510,   114,   115,   511,   512,   513,   514,   515,
     517,   710,   724,   304,   518,   520,   161,   519,   479,   521,
     522,   523,   480,   525,   529,   608,   530,   526,   527,   533,
     534,   532,   712,   725,   305,   536,   535,   537,   538,   482,
     539,   540,   544,   541,   624,   542,   543,   545,    94,   547,
     549,   550,   162,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   551,   713,   555,
     306,   556,   557,   558,   559,   483,   560,    32,   564,   565,
     566,   567,   568,   569,   835,   581,   570,   571,   572,   573,
     574,   481,   577,   578,   579,   590,   580,   589,   623,   734,
      94,   655,   615,   659,   663,   667,   582,   687,   736,   583,
     740,   588,   591,   592,   593,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   609,   744,   610,   748,
     750,   760,   611,   761,   762,   763,   764,   772,   622,   771,
     775,   774,   777,   778,   780,   781,   813,   784,   791,   790,
     792,   793,   794,   795,   796,   797,   802,   803,   804,   819,
     816,   818,   822,   821,   824,   825,   837,   831,   827,   832,
     833,   834,   840,   836,   838,   839,   841,   873,   874,   880,
     881,   875,   876,   877,   878,   886,   882,   883,   884,   887,
     888,   891,   917,   890,   898,   918,   977,   923,   942,   924,
     939,   919,   920,   921,   932,   934,   935,   639,   936,   940,
     175,   647,   947,   249,   270,   948,   268,   949,   953,   849,
     269,   176,   951,   854,   177,   271,   971,   178,   972,   285,
     850,   191,   973,   851,   263,   179,   852,   281,   976,   952,
     864,   978,   677,   449,   853,   710,   627,   625,   561,   474,
     724,   654,   842,   979,   868,   981,   477,   197,   869,   872,
     209,   879,   531,   227,   871,   844,   712,   192,   902,   843,
     264,   725,   903,   282,   946,   500,   865,   867,   202,   241,
     846,   211,   845,   189,   229,   848,   847,   892,   893,   904,
     524,   894,   863,   502,   885,   735,   528,   889,   895,   508,
     896,   732,   713,   897,   626,   546,   950,   969,   911,   980,
       0,     0,   516,     0,   203,     0,     0,   212,     0,   548,
     230,     0,     0,     0,     0,   905,     0,     0,     0,     0,
     198,     0,     0,   210,     0,     0,   228,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   849,     0,     0,     0,   854,
       0,     0,     0,     0,     0,     0,   850,     0,     0,   851,
       0,   933,   852,     0,   902,     0,   864,     0,   903,     0,
     853,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   904,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   865,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   863,     0,
       0,   905
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    16,    72,    73,    74,    75,    76,    79,    78,    79,
      80,    81,   571,    79,    73,   567,   779,    73,    79,   568,
      73,   779,   779,    72,    73,    74,    75,    76,    73,    78,
      79,     5,    81,     7,     7,     9,    38,   779,   779,   779,
       3,    77,     0,    10,   153,     8,    12,    13,     7,    51,
      52,    53,    54,    55,    56,    57,     7,    84,    85,    72,
      73,    74,    75,    76,     3,    78,    79,     7,    81,     8,
       3,   123,   124,   125,   126,     8,    73,    74,    75,    76,
      31,    32,    33,    34,    38,    84,    85,    38,     3,     7,
      56,    57,    16,     8,    37,    49,     7,    48,     7,    50,
      73,    25,    56,    57,   156,    56,    57,    58,    59,    60,
      61,    62,    63,    31,    32,    33,    34,   153,    36,     7,
      38,    39,    73,    74,   130,     7,   153,   133,   134,   135,
      81,     3,    56,    57,     3,     3,     8,     6,    56,    57,
       8,    59,    60,     3,    62,    63,     7,     3,     8,     3,
       7,   153,     8,     3,     8,    73,     3,   128,     8,     7,
     127,     8,   925,    81,     7,    16,     7,   925,   925,   136,
     137,   138,     3,    97,    98,    99,   100,     8,     7,   153,
     154,   155,   156,   925,   925,   925,   153,   153,    39,     7,
      41,    42,    38,    39,    45,    46,    47,    11,     3,   153,
      14,    15,   153,     8,     3,    56,    57,   120,   121,     8,
      56,    57,    56,    57,    94,    95,    96,    31,    32,    33,
      34,    35,    36,    37,    38,     3,    72,     3,     6,   153,
     779,     3,     8,   785,     3,   153,     8,     3,   787,     8,
       3,     6,    56,    57,    38,     8,   805,    39,    40,    41,
      42,    43,    44,    67,    68,    69,    70,    71,     4,   103,
     104,     3,    56,    57,    56,    57,     8,     8,   338,    83,
       3,     3,    86,     3,     3,     8,     8,    71,     8,    93,
       4,    75,    76,    77,    78,    79,    80,   101,   102,     4,
       4,   105,    87,    88,    89,    90,    91,    92,   368,     4,
     370,     3,   153,     3,   370,     3,     8,   153,     8,   153,
       8,     4,   382,   328,   329,   385,     4,    77,    78,   368,
      80,   370,   392,   382,     4,     3,   382,     3,     6,   382,
       6,     3,   402,   382,     6,     4,   385,   382,     4,   153,
       4,     4,   412,   392,     4,   417,     4,   417,    64,    65,
      66,   417,     8,   402,     3,   368,   417,   370,     8,   153,
      39,   153,     4,   412,     4,     8,   436,     3,   417,   382,
       4,     4,   385,   370,     3,   154,   925,    56,    57,   392,
      17,    18,    19,    20,     8,   382,     4,   436,   385,   402,
     509,   510,   511,     4,     4,   392,     4,     4,     4,   412,
       4,    16,   153,     4,   417,   402,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     4,     4,     4,     4,
       4,     4,     4,   436,    39,     4,   154,   154,   154,   154,
       4,   446,   447,   448,     4,     4,     4,     4,     4,     4,
       4,   154,     4,     4,     4,     4,     4,   462,     4,     4,
     129,     4,   131,   132,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,     4,   156,
       4,     4,     4,   154,   153,     4,     4,     4,     4,   156,
       4,     4,     4,   154,   154,   555,   556,   557,     4,   154,
     556,   557,     4,    56,    57,     4,     4,     4,     4,     4,
       4,   571,   572,   573,     4,     4,   555,   154,   578,     4,
       4,   156,   578,     4,     4,   530,     4,   156,   156,     4,
       4,   156,   571,   572,   573,     4,   154,   154,   154,   578,
       4,     4,     4,   156,   549,   156,   156,     4,   153,     4,
       4,     7,   555,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,     7,   571,     7,
     573,     7,     7,     5,     5,   578,     5,     7,     5,     5,
       5,     5,     5,     5,   154,   153,     7,     7,     7,     7,
       5,   578,     8,     3,     5,     7,     5,     5,     5,     4,
     153,     7,   122,     7,     7,     7,   153,     7,     7,   153,
       7,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,     7,   153,    82,
       7,     4,   153,     4,     4,     4,     4,     3,   153,     6,
       3,     6,     6,     3,     6,     3,   153,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     153,     6,     3,     6,     6,     3,   154,     4,     8,     4,
       4,     4,     4,   156,   156,   154,     4,   154,   154,     4,
       4,   154,   154,   154,   154,     4,   154,   154,   154,     4,
       4,     3,   153,     6,     4,   153,   156,     8,     4,     8,
       8,   153,   153,   153,   153,   153,   153,   767,   153,   153,
     770,   767,     4,   773,   776,   154,   776,     4,     7,   779,
     776,   770,     5,   779,   770,   776,     4,   770,     4,   789,
     779,   770,     4,   779,   773,   770,   779,   776,     4,   153,
     779,   154,   566,   338,   779,   805,   555,   550,   461,   364,
     810,   557,   767,   154,   782,   153,   368,   817,   785,   791,
     820,   798,   420,   823,   789,   772,   805,   770,   828,   770,
     773,   810,   828,   776,   925,   382,   779,   781,   817,    77,
     775,   820,   773,   770,   823,   778,   776,   817,   819,   828,
     412,   820,   779,   385,   805,   578,   417,   810,   822,   392,
     823,   573,   805,   825,   551,   436,   944,   957,   829,   974,
      -1,    -1,   402,    -1,   817,    -1,    -1,   820,    -1,   439,
     823,    -1,    -1,    -1,    -1,   828,    -1,    -1,    -1,    -1,
     817,    -1,    -1,   820,    -1,    -1,   823,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   925,    -1,    -1,    -1,   925,
      -1,    -1,    -1,    -1,    -1,    -1,   925,    -1,    -1,   925,
      -1,   886,   925,    -1,   944,    -1,   925,    -1,   944,    -1,
     925,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   944,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   925,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   925,    -1,
      -1,   944
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     5,     7,     9,   153,   154,   155,   156,   173,   174,
     175,   180,     7,   189,     7,   195,     7,   206,     7,   283,
       7,   358,     7,   374,     7,   391,     7,   310,     7,   316,
       7,   340,     7,   259,     7,   450,     7,   485,   181,   176,
     190,   196,   207,   284,   359,   375,   392,   311,   317,   341,
     260,   451,   486,   173,   182,   183,   153,   178,   179,    10,
     127,   136,   137,   138,   153,   188,   191,   192,   193,   477,
     479,   481,   483,    11,    14,    15,    31,    32,    33,    34,
      35,    36,    37,    38,    56,    57,    67,    68,    69,    70,
      71,    83,    86,    93,   101,   102,   105,   188,   197,   198,
     199,   200,   201,   202,   203,   204,   213,   215,   239,   245,
     251,   253,   267,   277,   300,   308,   334,   364,   366,   414,
     424,   436,   437,   448,    12,    13,   188,   208,   209,   210,
     212,   364,   366,     7,    48,    50,    58,    59,    60,    61,
      62,    63,    73,    74,    81,   188,   199,   200,   201,   202,
     285,   286,   287,   289,   291,   293,   295,   298,   299,   334,
     352,   364,   366,   368,   385,   410,    49,   188,   334,   360,
     361,   362,   364,   366,    51,    52,    53,    54,    55,   188,
     334,   364,   366,   376,   377,   378,   380,   381,   383,   384,
      71,    75,    76,    77,    78,    79,    80,   188,   334,   364,
     366,   393,   394,   395,   396,   398,   400,   402,   404,   406,
     408,   308,    16,    39,    41,    42,    45,    46,    47,   188,
     229,   318,   319,   320,   321,   322,   323,   324,   326,   328,
     330,   331,   333,   364,   366,    40,    43,    44,   188,   229,
     322,   328,   342,   343,   344,   345,   346,   348,   349,   350,
     351,   364,   366,    84,    85,   188,   261,   262,   263,   265,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   188,   364,   366,   452,   453,   454,
     455,   457,   459,   460,   462,   463,   464,   467,   469,   470,
     471,   472,   475,   128,   487,   488,   489,     6,     3,     4,
       8,     3,   194,   484,   478,   480,   482,     4,     3,     8,
     205,   214,   216,     4,     4,     4,     4,     4,   278,   309,
     335,   365,   367,   301,   240,   252,   246,   415,   254,   268,
     425,     4,   438,   449,     3,     8,   211,     4,     3,     8,
     417,   353,   369,   288,   290,   292,     4,     4,   296,   294,
     386,   411,     3,     8,   363,     3,     8,   379,     4,   382,
       4,     4,     3,     8,   409,   397,   399,   401,   403,   405,
     407,     8,     3,     8,   325,   230,     4,   329,   327,   332,
       4,     8,     3,   347,     4,     4,     8,     3,   264,   266,
       3,     8,     4,   456,   458,     4,   461,     4,     4,   465,
     468,     4,     4,     4,   473,   476,     3,     8,   490,     3,
       8,   173,   173,   153,     4,     4,     4,     4,     4,   192,
       4,     4,     4,   154,   154,   154,   154,   154,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   154,     4,     4,   198,     4,   156,   209,    72,   188,
     229,   334,   364,   366,   418,   419,   420,   421,   422,     4,
       4,     4,     4,     4,   154,   156,     4,     4,     4,     4,
     286,     4,   361,     4,   154,     4,   154,   154,   377,     4,
       4,     4,     4,     4,     4,     4,   395,     4,     4,   154,
       4,     4,     4,   156,   320,     4,   156,   156,   344,     4,
       4,   262,   156,     4,     4,   154,     4,   154,   154,     4,
       4,   156,   156,   156,     4,     4,   453,     4,   488,     4,
       7,     7,   173,   173,   173,     7,     7,     7,     5,     5,
       5,   175,   177,   173,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   184,   423,     8,     3,     5,
       5,   153,   153,   153,    64,    65,    66,   297,   153,     5,
       7,   153,   153,   153,   184,   184,   184,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   173,   153,
     153,   153,   120,   121,   466,   122,   123,   124,   125,   126,
     156,   474,   153,     5,   173,   197,   487,   208,    16,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,   188,
     217,   218,   219,   222,   224,   226,   228,   229,   231,   232,
     233,   234,   235,   237,   217,     7,   279,   280,   281,     7,
     312,   313,   314,     7,   336,   337,   338,     7,   302,   303,
     304,    77,   153,   241,   242,   243,   244,   182,    78,    80,
     243,   247,   248,   249,   250,   293,   416,     7,   255,   256,
     257,    87,    88,    89,    90,    91,    92,   269,   270,   271,
     272,   273,   274,   275,   276,    16,    97,    98,    99,   100,
     188,   231,   364,   366,   426,   427,   428,   431,   432,   434,
     435,    57,   103,   104,   188,   364,   439,   440,   441,   443,
     445,   446,   452,   185,     4,   420,     7,   354,   355,   356,
       7,   370,   371,   372,     7,   387,   388,   389,    82,   412,
       7,   491,   492,     8,     8,     8,   220,   223,   225,   227,
       4,     4,     4,     4,     4,   236,   238,     3,     8,     8,
     282,     6,     3,   315,     6,     3,   339,     6,     3,   305,
       6,     3,     3,     6,     6,     3,     6,     3,     6,   258,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     429,   433,     4,     4,     4,     3,     8,   447,   442,   444,
       3,     8,     8,   153,   186,   187,   153,   357,     6,     3,
     373,     6,     3,   390,     6,     3,   413,     8,   493,     3,
       6,     4,     4,     4,     4,   154,   156,   154,   156,   154,
       4,     4,   218,   285,   281,   318,   314,   342,   338,   188,
     199,   200,   201,   202,   229,   277,   289,   291,   293,   295,
     299,   306,   307,   334,   364,   366,   410,   304,   242,   248,
     293,   261,   257,   154,   154,   154,   154,   154,   154,   270,
       4,     4,   154,   154,   154,   427,     4,     4,     4,   440,
       6,     3,   360,   356,   376,   372,   393,   389,     4,   129,
     131,   132,   188,   229,   364,   366,   494,   495,   496,   497,
     499,   492,    17,    18,    19,    20,   221,   153,   153,   153,
     153,   153,     8,     8,     8,     3,     8,     8,    94,    95,
      96,   430,   153,   173,   153,   153,   153,     8,     8,     8,
     153,   500,     4,   498,     3,     8,   307,     4,   154,     4,
     495,     5,   153,     7,   501,   502,   503,     3,     6,   130,
     133,   134,   135,   504,   505,   506,   508,   509,   510,   502,
     507,     4,     4,     4,     3,     8,     4,   156,   154,   154,
     505,   153
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
  {
       0,   157,   159,   158,   160,   158,   161,   158,   162,   158,
     163,   158,   164,   158,   165,   158,   166,   158,   167,   158,
     168,   158,   169,   158,   170,   158,   171,   158,   172,   158,
     173,   173,   173,   173,   173,   173,   173,   174,   176,   175,
     177,   178,   178,   179,   179,   181,   180,   182,   182,   183,
     183,   185,   184,   186,   186,   187,   187,   188,   190,   189,
     191,   191,   192,   192,   192,   192,   192,   192,   194,   193,
     196,   195,   197,   197,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   199,
     200,   201,   202,   203,   205,   204,   207,   206,   208,   208,
     209,   209,   209,   209,   209,   211,   210,   212,   214,   213,
     216,   215,   217,   217,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   220,   219,   221,
     221,   221,   221,   223,   222,   225,   224,   227,   226,   228,
     230,   229,   231,   232,   233,   234,   236,   235,   238,   237,
     240,   239,   241,   241,   242,   242,   243,   244,   246,   245,
     247,   247,   248,   248,   248,   249,   250,   252,   251,   254,
     253,   255,   255,   256,   256,   258,   257,   260,   259,   261,
     261,   261,   262,   262,   264,   263,   266,   265,   268,   267,
     269,   269,   270,   270,   270,   270,   270,   270,   271,   272,
     273,   274,   275,   276,   278,   277,   279,   279,   280,   280,
     282,   281,   284,   283,   285,   285,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   288,   287,   290,   289,   292,
     291,   294,   293,   296,   295,   297,   297,   297,   298,   299,
     301,   300,   302,   302,   303,   303,   305,   304,   306,   306,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   309,   308,   311,   310,
     312,   312,   313,   313,   315,   314,   317,   316,   318,   318,
     319,   319,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   321,   322,   323,   325,   324,   327,   326,   329,
     328,   330,   332,   331,   333,   335,   334,   336,   336,   337,
     337,   339,   338,   341,   340,   342,   342,   343,   343,   344,
     344,   344,   344,   344,   344,   344,   344,   344,   345,   347,
     346,   348,   349,   350,   351,   353,   352,   354,   354,   355,
     355,   357,   356,   359,   358,   360,   360,   361,   361,   361,
     361,   361,   363,   362,   365,   364,   367,   366,   369,   368,
     370,   370,   371,   371,   373,   372,   375,   374,   376,   376,
     377,   377,   377,   377,   377,   377,   377,   377,   377,   379,
     378,   380,   382,   381,   383,   384,   386,   385,   387,   387,
     388,   388,   390,   389,   392,   391,   393,   393,   394,   394,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   397,   396,   399,   398,   401,   400,   403,   402,   405,
     404,   407,   406,   409,   408,   411,   410,   413,   412,   415,
     414,   416,   416,   417,   293,   418,   418,   419,   419,   420,
     420,   420,   420,   420,   420,   421,   423,   422,   425,   424,
     426,   426,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   429,   428,   430,   430,   430,   431,   433,   432,   434,
     435,   436,   438,   437,   439,   439,   440,   440,   440,   440,
     440,   442,   441,   444,   443,   445,   447,   446,   449,   448,
     451,   450,   452,   452,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   454,   456,   455,   458,   457,   459,   461,   460,   462,
     463,   465,   464,   466,   466,   468,   467,   469,   470,   471,
     473,   472,   474,   474,   474,   474,   474,   476,   475,   478,
     477,   480,   479,   482,   481,   484,   483,   486,   485,   487,
     487,   488,   490,   489,   491,   491,   493,   492,   494,   494,
     495,   495,   495,   495,   495,   495,   495,   496,   498,   497,
     500,   499,   501,   501,   503,   502,   504,   504,   505,   505,
     505,   505,   507,   506,   508,   509,   510
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     1,     0,     4,     0,     6,
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
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"all\"", "\"shared-networks\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"", "\"test\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"Logging\"", "\"loggers\"", "\"output_options\"", "\"output\"",
  "\"debuglevel\"", "\"severity\"", "\"flush\"", "\"maxsize\"",
  "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"", "\"Control-agent\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEFS", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp6_object", "$@19", "sub_dhcp6",
  "$@20", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@21",
  "sub_interfaces6", "$@22", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@23", "re_detect",
  "lease_database", "$@24", "hosts_database", "$@25",
  "database_map_params", "database_map_param", "database_type", "$@26",
  "db_type", "user", "$@27", "password", "$@28", "host", "$@29", "port",
  "name", "$@30", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@31", "keyspace", "$@32", "mac_sources", "$@33",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@34",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@35",
  "hooks_libraries", "$@36", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@37",
  "sub_hooks_library", "$@38", "hooks_params", "hooks_param", "library",
  "$@39", "parameters", "$@40", "expired_leases_processing", "$@41",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@42",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@43",
  "sub_subnet6", "$@44", "subnet6_params", "subnet6_param", "subnet",
  "$@45", "interface", "$@46", "interface_id", "$@47", "client_class",
  "$@48", "reservation_mode", "$@49", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@50", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@51",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@52", "sub_option_def_list", "$@53", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@54",
  "sub_option_def", "$@55", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@56",
  "option_def_record_types", "$@57", "space", "$@58", "option_def_space",
  "option_def_encapsulate", "$@59", "option_def_array", "option_data_list",
  "$@60", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@61", "sub_option_data", "$@62",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@63",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@64", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@65", "sub_pool6", "$@66",
  "pool_params", "pool_param", "pool_entry", "$@67", "user_context",
  "$@68", "comment", "$@69", "pd_pools_list", "$@70",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@71", "sub_pd_pool", "$@72", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@73", "pd_prefix_len", "excluded_prefix", "$@74",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@75",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@76", "sub_reservation", "$@77", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@78", "prefixes", "$@79", "duid", "$@80", "hw_address", "$@81",
  "hostname", "$@82", "flex_id_value", "$@83",
  "reservation_client_classes", "$@84", "relay", "$@85", "relay_map",
  "$@86", "client_classes", "$@87", "client_classes_list", "$@88",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@89",
  "server_id", "$@90", "server_id_params", "server_id_param",
  "server_id_type", "$@91", "duid_type", "htype", "identifier", "$@92",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@93",
  "control_socket_params", "control_socket_param", "socket_type", "$@94",
  "socket_name", "$@95", "socket_user_context", "socket_comment", "$@96",
  "dhcp_ddns", "$@97", "sub_dhcp_ddns", "$@98", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@99",
  "server_ip", "$@100", "server_port", "sender_ip", "$@101", "sender_port",
  "max_queue_size", "ncr_protocol", "$@102", "ncr_protocol_value",
  "ncr_format", "$@103", "always_include_fqdn", "override_no_update",
  "override_client_update", "replace_client_name", "$@104",
  "replace_client_name_value", "generated_prefix", "$@105",
  "dhcp4_json_object", "$@106", "dhcpddns_json_object", "$@107",
  "control_agent_json_object", "$@108", "logging_object", "$@109",
  "sub_logging", "$@110", "logging_params", "logging_param", "loggers",
  "$@111", "loggers_entries", "logger_entry", "$@112", "logger_params",
  "logger_param", "debuglevel", "severity", "$@113", "output_options_list",
  "$@114", "output_options_list_content", "output_entry", "$@115",
  "output_params_list", "output_params", "output", "$@116", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   238,   238,   238,   239,   239,   240,   240,   241,   241,
     242,   242,   243,   243,   244,   244,   245,   245,   246,   246,
     247,   247,   248,   248,   249,   249,   250,   250,   251,   251,
     259,   260,   261,   262,   263,   264,   265,   268,   273,   273,
     284,   287,   288,   291,   295,   302,   302,   309,   310,   313,
     317,   324,   324,   331,   332,   335,   339,   350,   360,   360,
     375,   376,   380,   381,   382,   383,   384,   385,   388,   388,
     403,   403,   412,   413,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   445,
     450,   455,   460,   465,   470,   470,   481,   481,   490,   491,
     494,   495,   496,   497,   498,   501,   501,   511,   517,   517,
     529,   529,   541,   542,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   560,   560,   567,
     568,   569,   570,   573,   573,   581,   581,   589,   589,   597,
     602,   602,   610,   615,   620,   625,   630,   630,   638,   638,
     647,   647,   657,   658,   661,   662,   665,   670,   675,   675,
     685,   686,   689,   690,   691,   694,   699,   706,   706,   716,
     716,   726,   727,   730,   731,   734,   734,   744,   744,   754,
     755,   756,   759,   760,   763,   763,   771,   771,   779,   779,
     790,   791,   794,   795,   796,   797,   798,   799,   802,   807,
     812,   817,   822,   827,   835,   835,   848,   849,   852,   853,
     860,   860,   886,   886,   897,   898,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   914,   915,
     916,   917,   918,   919,   920,   923,   923,   931,   931,   939,
     939,   947,   947,   955,   955,   962,   963,   964,   967,   972,
     980,   980,   991,   992,   996,   997,  1000,  1000,  1008,  1009,
    1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1034,  1034,  1047,  1047,
    1056,  1057,  1060,  1061,  1066,  1066,  1081,  1081,  1095,  1096,
    1099,  1100,  1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,
    1111,  1112,  1115,  1117,  1122,  1124,  1124,  1132,  1132,  1140,
    1140,  1148,  1150,  1150,  1158,  1167,  1167,  1179,  1180,  1185,
    1186,  1191,  1191,  1203,  1203,  1215,  1216,  1221,  1222,  1227,
    1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,  1238,  1240,
    1240,  1248,  1250,  1252,  1257,  1265,  1265,  1277,  1278,  1281,
    1282,  1285,  1285,  1295,  1295,  1304,  1305,  1308,  1309,  1310,
    1311,  1312,  1315,  1315,  1323,  1323,  1330,  1330,  1342,  1342,
    1354,  1355,  1358,  1359,  1362,  1362,  1374,  1374,  1386,  1387,
    1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,  1401,
    1401,  1409,  1414,  1414,  1422,  1427,  1435,  1435,  1445,  1446,
    1449,  1450,  1453,  1453,  1462,  1462,  1471,  1472,  1475,  1476,
    1480,  1481,  1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,
    1490,  1493,  1493,  1503,  1503,  1513,  1513,  1521,  1521,  1529,
    1529,  1537,  1537,  1545,  1545,  1558,  1558,  1568,  1568,  1579,
    1579,  1589,  1590,  1593,  1593,  1603,  1604,  1607,  1608,  1611,
    1612,  1613,  1614,  1615,  1616,  1619,  1621,  1621,  1632,  1632,
    1644,  1645,  1648,  1649,  1650,  1651,  1652,  1653,  1654,  1655,
    1656,  1659,  1659,  1666,  1667,  1668,  1671,  1676,  1676,  1684,
    1689,  1696,  1703,  1703,  1713,  1714,  1717,  1718,  1719,  1720,
    1721,  1724,  1724,  1732,  1732,  1740,  1742,  1742,  1751,  1751,
    1763,  1763,  1773,  1774,  1777,  1778,  1779,  1780,  1781,  1782,
    1783,  1784,  1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,
    1793,  1796,  1801,  1801,  1809,  1809,  1817,  1822,  1822,  1830,
    1835,  1840,  1840,  1848,  1849,  1852,  1852,  1860,  1865,  1870,
    1875,  1875,  1883,  1886,  1889,  1892,  1895,  1901,  1901,  1911,
    1911,  1918,  1918,  1925,  1925,  1938,  1938,  1948,  1948,  1959,
    1960,  1964,  1968,  1968,  1980,  1981,  1985,  1985,  1993,  1994,
    1997,  1998,  1999,  2000,  2001,  2002,  2003,  2006,  2011,  2011,
    2019,  2019,  2029,  2030,  2033,  2033,  2041,  2042,  2045,  2046,
    2047,  2048,  2051,  2051,  2059,  2064,  2069
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1167
} } // isc::dhcp
#line 4577 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2074 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
