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
      case 463: // ncr_protocol_value
      case 471: // replace_client_name_value
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
      case 463: // ncr_protocol_value
      case 471: // replace_client_name_value
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

      case 463: // ncr_protocol_value

#line 229 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 471: // replace_client_name_value

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
      case 463: // ncr_protocol_value
      case 471: // replace_client_name_value
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
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        user_context->set("comment", old->get("comment"));
    }
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2238 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr parent = ctx.stack_.back();
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        old->set("comment", yystack_[0].value.as< std::string > ());
    } else {
        ElementPtr e(new MapElement(ctx.loc2pos(yystack_[3].location)));
        e->set("comment", yystack_[0].value.as< std::string > ());
        top->set("user-context", e);
    }
    ctx.leave();
}
#line 2255 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2266 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2285 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 385:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 386:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 387:
#line 1396 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2319 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 399:
#line 1419 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 400:
#line 1421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2337 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 401:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2346 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 402:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 403:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 404:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 405:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2382 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2412 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1484 "dhcp6_parser.yy" // lalr1.cc:859
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 431:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2451 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 432:
#line 1516 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 433:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 434:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 435:
#line 1531 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2488 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 436:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 437:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 438:
#line 1541 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1547 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2542 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2552 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 443:
#line 1563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2563 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 444:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2572 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 445:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2583 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 446:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2592 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 447:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 448:
#line 1588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2610 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 449:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 450:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2640 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 466:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 467:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 468:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1655 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2690 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 481:
#line 1677 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 482:
#line 1679 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 483:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2713 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 484:
#line 1685 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2719 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 485:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2725 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 486:
#line 1689 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 487:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 488:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 489:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 490:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 491:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 492:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2790 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 493:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2799 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1742 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2817 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2846 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2857 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1772 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2867 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 530:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 531:
#line 1818 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 532:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1826 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2931 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2939 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 535:
#line 1833 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 536:
#line 1839 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 539:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 540:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2990 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 541:
#line 1858 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2996 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 542:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3004 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 543:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3014 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 544:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 545:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3032 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3041 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 3066 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3074 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 551:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 552:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3090 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1904 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3099 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1910 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 555:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3117 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 556:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 557:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3134 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 558:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3142 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 559:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3151 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 560:
#line 1934 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3159 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1936 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1947 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3179 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1957 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3198 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 3206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 569:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 570:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3226 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 573:
#line 1994 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3236 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 574:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 584:
#line 2015 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 585:
#line 2020 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3261 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 586:
#line 2022 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 587:
#line 2028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3282 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 588:
#line 2033 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3291 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 591:
#line 2042 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3301 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 592:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3309 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 599:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3317 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 600:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 601:
#line 2068 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3336 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 602:
#line 2073 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 603:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3354 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3358 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -758;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     306,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,    60,    28,    68,    72,    74,
      82,    84,   110,   117,   149,   154,   160,   166,   170,   187,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,    28,    22,
      32,   482,    36,    40,    70,     2,   177,   194,   106,   230,
     -33,   320,    86,  -758,   229,   240,   254,   269,   276,  -758,
    -758,  -758,  -758,  -758,   295,  -758,    35,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,   297,   301,   305,   307,
     313,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,   316,  -758,  -758,  -758,    79,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,   327,  -758,   115,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,   333,
     334,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
     168,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,   203,
    -758,  -758,  -758,  -758,  -758,   337,  -758,   341,   342,  -758,
    -758,  -758,  -758,   204,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,   344,   311,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,   346,  -758,  -758,   351,  -758,  -758,  -758,   354,  -758,
    -758,   353,   359,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,   360,   361,  -758,  -758,
    -758,  -758,   362,   364,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,   214,  -758,  -758,  -758,
     368,  -758,  -758,   369,  -758,   371,   374,  -758,  -758,   375,
     378,   384,  -758,  -758,  -758,  -758,  -758,   222,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,   241,  -758,  -758,  -758,    28,    28,
    -758,   236,   386,   389,   390,   392,   393,  -758,    32,  -758,
     394,   395,   396,   249,   250,   251,   253,   255,   404,   406,
     407,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   270,   419,   436,   482,  -758,   437,   303,    36,  -758,
      38,   456,   457,   458,   459,   460,   312,   309,   463,   464,
     465,   466,    40,  -758,   467,    70,  -758,   468,   321,   470,
     322,   323,     2,  -758,   474,   475,   476,   477,   478,   479,
     480,  -758,   177,  -758,   484,   485,   338,   490,   491,   494,
     343,  -758,   106,   496,   348,   349,  -758,   230,   503,   505,
      53,  -758,   355,   506,   517,   373,   521,   376,   377,   524,
     528,   379,   380,   381,   529,   530,   320,  -758,   536,    86,
    -758,  -758,  -758,   537,   535,   539,    28,    28,    28,  -758,
     540,   541,   547,  -758,  -758,  -758,  -758,  -758,   538,   550,
     551,   552,   405,   558,   559,   561,   564,   565,   566,   567,
     569,  -758,   570,   571,  -758,   568,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,   549,   576,  -758,  -758,  -758,   575,
     577,   428,   432,   433,  -758,  -758,   284,   438,   584,   583,
    -758,   439,  -758,   440,  -758,   441,  -758,  -758,  -758,   568,
     568,   568,   442,   443,   444,   445,  -758,   446,   447,  -758,
     448,   449,   450,  -758,  -758,   451,  -758,  -758,  -758,   452,
      28,  -758,  -758,   453,   454,  -758,   455,  -758,  -758,    29,
     487,  -758,  -758,  -758,    18,   461,  -758,   605,  -758,    28,
     482,    86,  -758,  -758,  -758,    36,   174,   174,   604,   606,
     608,  -758,  -758,  -758,   609,   -38,    28,    80,    43,   610,
     150,   163,    83,   320,  -758,  -758,   614,  -758,    38,   612,
     613,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,   615,
     542,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,   616,  -758,   242,   243,   272,  -758,  -758,
    -758,  -758,   617,   621,   622,   623,   624,  -758,  -758,  -758,
     273,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,   275,  -758,   625,   626,  -758,  -758,
     627,   629,  -758,  -758,   628,   633,  -758,  -758,   631,   635,
    -758,  -758,  -758,    63,  -758,  -758,  -758,   634,  -758,  -758,
    -758,   122,  -758,  -758,  -758,  -758,   128,  -758,   636,   638,
    -758,   639,   640,   641,   642,   643,   644,   285,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,   645,   646,   647,
    -758,  -758,  -758,  -758,   286,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,   287,  -758,  -758,  -758,
     288,   486,   499,  -758,  -758,   648,   650,  -758,  -758,   649,
     653,  -758,  -758,   651,   655,  -758,  -758,   652,  -758,   202,
    -758,  -758,  -758,  -758,   657,   658,   659,   660,   511,   510,
     513,   512,   515,   666,   667,   174,  -758,  -758,    40,  -758,
     604,   106,  -758,   606,   230,  -758,   608,    73,  -758,   609,
     -38,  -758,  -758,    80,  -758,    43,  -758,   -33,  -758,   610,
     518,   519,   520,   522,   523,   525,   150,  -758,   671,   674,
     526,   527,   531,   163,  -758,   678,   679,    83,  -758,  -758,
    -758,   680,   656,  -758,    70,  -758,   612,     2,  -758,   613,
     177,  -758,   615,   683,  -758,   153,   616,  -758,   247,   544,
     553,   557,  -758,  -758,  -758,  -758,  -758,   562,   563,  -758,
     289,  -758,   676,  -758,   681,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,   299,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,   300,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,   133,   574,  -758,
    -758,  -758,  -758,   578,   579,  -758,  -758,   581,   310,  -758,
     326,  -758,   682,  -758,   582,  -758,   684,  -758,  -758,  -758,
    -758,  -758,   332,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,    73,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,   687,   546,   688,   153,
    -758,  -758,   607,  -758,   585,  -758,   686,  -758,  -758,   215,
    -758,   -89,   686,  -758,  -758,   690,   698,   699,   336,  -758,
    -758,  -758,  -758,  -758,  -758,   716,   573,   586,   587,   -89,
    -758,   589,  -758,  -758,  -758,  -758,  -758
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
     333,    23,   187,    25,   507,    27,   564,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   416,     0,   298,   335,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     562,   556,   558,   560,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   104,   118,   120,     0,     0,     0,     0,
       0,   214,   286,   325,   374,   376,   260,   160,   177,   168,
     449,   179,   198,   468,     0,   492,   505,    98,     0,    72,
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
       0,   529,   531,     0,   534,     0,     0,   538,   542,     0,
       0,     0,   547,   554,   527,   525,   526,     0,   509,   511,
     512,   513,   514,   515,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   569,     0,   566,   568,    46,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,   508,     0,     0,
     565,    50,    43,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   491,     0,     0,    73,     0,   117,   109,   466,   464,
     465,   461,   462,   463,     0,   456,   457,   459,   460,     0,
       0,     0,     0,     0,   258,   259,     0,     0,     0,     0,
     225,     0,   366,     0,   401,     0,   404,   405,   389,     0,
       0,     0,     0,     0,     0,     0,   419,     0,     0,   313,
       0,     0,     0,   324,   301,     0,   353,   354,   338,     0,
       0,   190,   528,     0,     0,   533,     0,   536,   537,     0,
       0,   544,   545,   546,     0,     0,   510,     0,   567,     0,
       0,     0,   557,   559,   561,     0,     0,     0,   216,   290,
     327,    40,   375,   377,   262,     0,    47,     0,     0,   181,
       0,     0,     0,     0,    51,   116,     0,   454,     0,   357,
     380,   246,   248,   250,   255,   256,   257,   254,   252,   408,
       0,   373,   400,   403,   444,   432,   434,   436,   438,   440,
     442,   316,   151,   320,   318,   323,   350,   195,   197,   530,
     532,   535,   540,   541,   539,   543,   549,   550,   551,   552,
     553,   548,   555,     0,    44,     0,     0,     0,   137,   143,
     145,   147,     0,     0,     0,     0,     0,   156,   158,   136,
       0,   122,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,     0,   220,     0,   217,   218,   294,
       0,   291,   292,   331,     0,   328,   329,   266,     0,   263,
     264,   166,   167,     0,   162,   164,   165,     0,   175,   176,
     172,     0,   170,   173,   174,   451,     0,   185,     0,   182,
     183,     0,     0,     0,     0,     0,     0,     0,   200,   202,
     203,   204,   205,   206,   207,   481,   487,     0,     0,     0,
     480,   477,   478,   479,     0,   470,   472,   475,   473,   474,
     476,   501,   503,   500,   498,   499,     0,   494,   496,   497,
       0,    53,     0,   458,   361,     0,   358,   359,   384,     0,
     381,   382,   412,     0,   409,   410,   447,     0,   573,     0,
     571,    69,   563,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   121,     0,   215,
       0,   298,   287,     0,   335,   326,     0,     0,   261,     0,
       0,   161,   178,     0,   169,     0,   450,     0,   180,     0,
       0,     0,     0,     0,     0,     0,     0,   199,     0,     0,
       0,     0,     0,     0,   469,     0,     0,     0,   493,   506,
      55,     0,    54,   467,     0,   356,     0,     0,   379,     0,
     416,   407,     0,     0,   446,     0,     0,   570,     0,     0,
       0,     0,   149,   152,   153,   154,   155,     0,     0,   123,
       0,   219,     0,   293,     0,   330,   285,   280,   282,   274,
     275,   270,   271,   272,   273,   279,   278,   281,     0,   268,
     276,   283,   284,   277,   265,   163,   171,   452,     0,   184,
     208,   209,   210,   211,   212,   213,   201,     0,     0,   486,
     489,   490,   471,     0,     0,   495,    52,     0,     0,   360,
       0,   383,     0,   411,     0,   587,     0,   585,   583,   577,
     581,   582,     0,   575,   579,   580,   578,   572,   139,   140,
     141,   142,   138,   144,   146,   148,   157,   159,   221,   295,
     332,     0,   267,   186,   483,   484,   485,   482,   488,   502,
     504,    56,   362,   385,   413,   448,     0,     0,     0,     0,
     574,   269,     0,   584,     0,   576,     0,   586,   591,     0,
     589,     0,     0,   588,   599,     0,     0,     0,     0,   593,
     595,   596,   597,   598,   590,     0,     0,     0,     0,     0,
     592,     0,   601,   602,   603,   594,   600
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,    -4,  -758,   111,  -758,
    -758,  -758,  -758,  -758,  -758,    64,  -758,  -125,  -758,  -758,
    -758,   -70,  -758,  -758,  -758,   398,  -758,  -758,  -758,  -758,
     180,   382,   -72,   -59,   -56,   -54,  -758,  -758,  -758,  -758,
    -758,   169,   383,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
     182,   -22,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,   -66,  -758,  -556,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,   -35,  -551,  -758,  -758,  -758,
    -758,   -34,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
     -41,  -758,  -758,  -758,   -31,   347,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,   -44,  -758,  -758,  -758,  -758,  -758,  -758,
    -757,  -758,  -758,  -758,   -17,  -758,  -758,  -758,    -7,   387,
    -758,  -758,  -756,  -758,  -755,  -758,  -561,  -758,  -749,  -758,
    -758,  -758,  -743,  -758,  -758,  -758,  -758,   -15,  -758,  -758,
    -159,   693,  -758,  -758,  -758,  -758,  -758,    -1,  -758,  -758,
    -758,     3,  -758,   363,  -758,   -61,  -758,  -758,  -758,  -758,
    -758,   -48,  -758,  -758,  -758,  -758,  -758,    10,  -758,  -758,
    -758,    -3,  -758,  -758,  -758,     5,  -758,   365,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,   -39,
    -758,  -758,  -758,   -30,   400,  -758,  -758,   -49,  -758,   -11,
    -758,  -758,  -758,  -758,  -758,   -36,  -758,  -758,  -758,   -37,
     397,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,   -32,  -758,  -758,  -758,   -29,  -758,   391,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -741,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,   208,  -758,  -758,  -758,  -758,  -758,  -758,
      -9,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,   -26,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,   224,   352,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,  -758,
    -758,  -758,  -758,  -758,  -758,  -758,  -758,   244,   366,  -758,
    -758,  -758,   -28,  -758,  -758,  -140,  -758,  -758,  -758,  -758,
    -758,  -758,  -152,  -758,  -758,  -168,  -758,  -758,  -758,  -758,
    -758
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     562,    87,    88,    41,    68,    84,    85,   575,   731,   811,
     812,   127,    43,    70,    96,    97,    98,   332,    45,    71,
     128,   129,   130,   131,   132,   133,   134,   135,   340,    47,
      72,   157,   158,   159,   366,   160,   136,   341,   137,   342,
     640,   641,   642,   754,   912,   643,   755,   644,   756,   645,
     757,   646,   250,   405,   648,   649,   650,   651,   652,   763,
     653,   764,   138,   354,   673,   674,   675,   676,   139,   356,
     681,   682,   683,   684,   140,   355,   141,   358,   688,   689,
     690,   787,    63,    80,   286,   287,   288,   418,   289,   419,
     142,   359,   697,   698,   699,   700,   701,   702,   703,   704,
     143,   348,   656,   657,   658,   768,    49,    73,   180,   181,
     182,   373,   183,   374,   184,   375,   185,   379,   186,   378,
     587,   187,   188,   144,   353,   668,   669,   670,   777,   858,
     859,   145,   349,    57,    77,   660,   661,   662,   771,    59,
      78,   251,   252,   253,   254,   255,   256,   257,   404,   258,
     408,   259,   407,   260,   261,   409,   262,   146,   350,   664,
     665,   666,   774,    61,    79,   272,   273,   274,   275,   276,
     413,   277,   278,   279,   280,   190,   371,   735,   736,   737,
     814,    51,    74,   199,   200,   201,   384,   147,   351,   148,
     352,   193,   372,   739,   740,   741,   817,    53,    75,   213,
     214,   215,   387,   216,   217,   389,   218,   219,   194,   380,
     743,   744,   745,   820,    55,    76,   231,   232,   233,   234,
     395,   235,   396,   236,   397,   237,   398,   238,   399,   239,
     400,   240,   394,   195,   381,   747,   823,   149,   357,   686,
     370,   484,   485,   486,   487,   488,   576,   150,   360,   714,
     715,   716,   798,   927,   717,   718,   799,   719,   720,   151,
     152,   362,   726,   727,   728,   805,   729,   806,   153,   363,
      65,    81,   307,   308,   309,   310,   423,   311,   424,   312,
     313,   426,   314,   315,   316,   429,   614,   317,   430,   318,
     319,   320,   321,   434,   621,   322,   435,    99,   334,   100,
     335,   101,   336,   102,   333,    67,    82,   324,   325,   326,
     438,   749,   750,   825,   902,   903,   904,   905,   938,   906,
     936,   949,   950,   951,   958,   959,   960,   965,   961,   962,
     963
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      95,   176,   156,   175,   197,   209,   227,   685,   249,   268,
     285,   304,    38,   269,   177,   711,   680,   178,   270,   179,
     852,   853,   854,   161,   191,   202,   211,   229,   856,   263,
     281,   271,   305,    31,   857,    32,   863,    33,   338,   671,
     113,   954,    89,   339,   955,   956,   957,   163,   154,   155,
     163,   283,   284,   204,   205,   206,   207,   208,   114,   115,
      30,   162,   192,   203,   212,   230,   780,   264,   282,   781,
     306,   106,   107,   108,   109,    42,   113,   243,   113,    44,
     163,    46,   364,   189,   198,   210,   228,   365,   164,    48,
     165,    50,   114,   115,   114,   115,   114,   115,   166,   167,
     168,   169,   170,   171,   106,   107,   108,   109,   113,   111,
     478,   113,   243,   172,   173,   672,   172,    52,   368,   196,
      94,   174,   242,   369,    54,   783,   114,   115,   784,   114,
     115,   785,   167,   168,   786,   170,   171,   283,   284,   114,
     115,   616,   617,   618,   619,   243,   172,   244,   245,   612,
     613,   246,   247,   248,   174,    94,    56,   671,   678,    90,
     679,    58,   114,   115,   852,   853,   854,    60,    91,    92,
      93,   382,   856,    62,   620,    86,   383,    64,   857,   705,
     863,    34,    35,    36,    37,    94,   721,   722,   633,    94,
     628,    94,   243,    94,    66,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   826,   385,   392,   827,   114,
     115,   386,   393,   243,   323,   113,   855,   420,   952,   114,
     115,   953,   421,    94,   867,   436,    94,   924,   925,   926,
     437,   112,   680,   114,   115,   327,    94,   691,   692,   693,
     694,   695,   696,   328,   439,   364,   439,   711,   220,   440,
     751,   752,   221,   222,   223,   224,   225,   226,   329,    94,
     706,   707,   708,   709,   908,   909,   910,   911,    95,   243,
     265,   244,   245,   266,   267,   368,   765,   330,   765,   331,
     753,   766,   895,   767,   896,   897,   114,   115,   796,   803,
     807,   436,   382,   797,   804,   808,   809,   918,   156,   337,
     479,   343,   921,   420,   480,   344,    94,   922,   923,   345,
     176,   346,   175,   385,   402,   197,    94,   347,   932,   161,
     361,   482,   209,   177,   441,   442,   178,    94,   179,   392,
      94,   367,   227,   191,   933,   939,   202,   376,   377,   969,
     940,   388,   249,   211,   970,   390,   391,   268,   584,   585,
     586,   269,   401,   229,   403,   406,   270,   162,   410,   483,
     855,   411,   412,   263,   414,   415,   304,   417,   281,   271,
     416,   192,   422,   425,   203,   427,   114,   115,   428,   431,
     481,   212,   432,    94,   594,   595,   596,   305,   433,   443,
     444,   230,   189,   445,   446,   198,   447,   448,   450,   451,
     452,   264,   210,   453,   454,   455,   282,   456,   458,   457,
     459,   460,   228,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   472,   471,   306,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     473,   475,   552,   553,   554,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   476,
     489,   490,   491,   492,   493,   495,   494,   496,   497,   498,
     499,   501,   503,    94,   505,   504,   506,   507,   509,   510,
     511,   512,   513,   514,   515,   156,   639,   639,   517,   518,
     647,   647,   519,   103,   520,   521,   104,   105,   522,   523,
     525,   710,   723,   304,   526,   527,   161,   529,   479,   530,
     533,   532,   480,   106,   107,   108,   109,   110,   111,   112,
     113,   534,   712,   724,   305,   536,   608,   535,   539,   482,
     537,   538,   540,   544,   545,   541,   542,   543,   114,   115,
     547,   549,   550,   558,   162,   624,   551,   555,   556,   116,
     117,   118,   119,   120,   557,   559,   560,   577,   563,    32,
     713,   725,   306,   564,   565,   121,   566,   483,   122,   567,
     568,   569,   561,   574,   570,   123,   571,   572,   573,   578,
     579,   581,   580,   124,   125,   582,   583,   126,   481,   589,
     590,   588,   591,   592,   593,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   609,   610,   611,   615,
     623,   655,   946,   659,   622,   663,   667,   687,   732,   734,
     738,   758,   742,   748,   746,   759,   760,   761,   762,   770,
     677,   769,   773,   772,   775,    94,   776,   778,   779,   810,
     782,   789,   788,   790,   791,   792,   793,   794,   795,   800,
     801,   802,   813,   816,   815,   818,   819,   821,   822,   887,
     824,   828,   829,   830,   831,   832,   833,   834,   835,   836,
     837,   838,   870,   871,   872,   877,   873,   874,   878,   875,
     879,   880,   883,   884,   919,   881,   886,   894,   937,   920,
     934,   942,   944,   948,   966,   639,   176,   913,   175,   647,
     943,   249,   967,   968,   268,   847,   914,   846,   269,   177,
     915,   851,   178,   270,   179,   916,   917,   285,   848,   191,
     971,   849,   263,   850,   627,   281,   271,   928,   861,   972,
     625,   929,   930,   710,   931,   935,   449,   723,   947,   654,
     973,   974,   976,   839,   197,   865,   474,   209,   869,   866,
     227,   477,   876,   841,   712,   898,   868,   192,   724,   899,
     264,   840,   941,   282,   864,   202,   862,   531,   211,   500,
     241,   229,   843,   845,   842,   524,   900,   889,   189,   844,
     890,   885,   528,   891,   888,   502,   733,   860,   546,   508,
     893,   892,   713,   516,   882,   626,   725,   730,   907,   945,
     964,   975,     0,   203,     0,   548,   212,     0,     0,   230,
       0,     0,     0,     0,   901,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   198,     0,     0,   210,     0,     0,
     228,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   847,
       0,   846,     0,     0,     0,   851,     0,     0,     0,     0,
       0,     0,   848,     0,     0,   849,     0,   850,     0,   898,
       0,     0,   861,   899,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     900,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     862,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   901,     0,
       0,   860
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      70,    73,    72,    73,    74,    75,    76,   568,    78,    79,
      80,    81,    16,    79,    73,   571,   567,    73,    79,    73,
     777,   777,   777,    72,    73,    74,    75,    76,   777,    78,
      79,    79,    81,     5,   777,     7,   777,     9,     3,    77,
      38,   130,    10,     8,   133,   134,   135,     7,    12,    13,
       7,    84,    85,    51,    52,    53,    54,    55,    56,    57,
       0,    72,    73,    74,    75,    76,     3,    78,    79,     6,
      81,    31,    32,    33,    34,     7,    38,    39,    38,     7,
       7,     7,     3,    73,    74,    75,    76,     8,    48,     7,
      50,     7,    56,    57,    56,    57,    56,    57,    58,    59,
      60,    61,    62,    63,    31,    32,    33,    34,    38,    36,
      72,    38,    39,    73,    74,   153,    73,     7,     3,    49,
     153,    81,    16,     8,     7,     3,    56,    57,     6,    56,
      57,     3,    59,    60,     6,    62,    63,    84,    85,    56,
      57,   123,   124,   125,   126,    39,    73,    41,    42,   120,
     121,    45,    46,    47,    81,   153,     7,    77,    78,   127,
      80,     7,    56,    57,   921,   921,   921,     7,   136,   137,
     138,     3,   921,     7,   156,   153,     8,     7,   921,    16,
     921,   153,   154,   155,   156,   153,   103,   104,    25,   153,
      16,   153,    39,   153,     7,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     3,     3,     3,     6,    56,
      57,     8,     8,    39,   128,    38,   777,     3,     3,    56,
      57,     6,     8,   153,   785,     3,   153,    94,    95,    96,
       8,    37,   783,    56,    57,     6,   153,    87,    88,    89,
      90,    91,    92,     3,     3,     3,     3,   803,    71,     8,
       8,     8,    75,    76,    77,    78,    79,    80,     4,   153,
      97,    98,    99,   100,    17,    18,    19,    20,   338,    39,
      40,    41,    42,    43,    44,     3,     3,     8,     3,     3,
       8,     8,   129,     8,   131,   132,    56,    57,     3,     3,
       3,     3,     3,     8,     8,     8,     8,     8,   368,     4,
     370,     4,     3,     3,   370,     4,   153,     8,     8,     4,
     382,     4,   382,     3,     3,   385,   153,     4,     8,   368,
       4,   370,   392,   382,   328,   329,   382,   153,   382,     3,
     153,     4,   402,   382,     8,     3,   385,     4,     4,     3,
       8,     4,   412,   392,     8,     4,     4,   417,    64,    65,
      66,   417,     8,   402,     8,     4,   417,   368,     4,   370,
     921,     8,     3,   412,     4,     4,   436,     3,   417,   417,
       8,   382,     4,     4,   385,     4,    56,    57,     4,     4,
     370,   392,     4,   153,   509,   510,   511,   436,     4,   153,
       4,   402,   382,     4,     4,   385,     4,     4,     4,     4,
       4,   412,   392,   154,   154,   154,   417,   154,     4,   154,
       4,     4,   402,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   154,   436,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
       4,     4,   446,   447,   448,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   156,
       4,     4,     4,     4,     4,   156,   154,     4,     4,     4,
       4,     4,     4,   153,     4,   154,   154,   154,     4,     4,
       4,     4,     4,     4,     4,   555,   556,   557,     4,     4,
     556,   557,   154,    11,     4,     4,    14,    15,     4,   156,
       4,   571,   572,   573,   156,   156,   555,     4,   578,     4,
       4,   156,   578,    31,    32,    33,    34,    35,    36,    37,
      38,     4,   571,   572,   573,     4,   530,   154,     4,   578,
     154,   154,     4,     4,     4,   156,   156,   156,    56,    57,
       4,     4,     7,     5,   555,   549,     7,     7,     7,    67,
      68,    69,    70,    71,     7,     5,     5,     8,   153,     7,
     571,   572,   573,     5,     5,    83,     5,   578,    86,     5,
       5,     5,   461,     5,     7,    93,     7,     7,     7,     3,
       5,   153,     5,   101,   102,   153,   153,   105,   578,     5,
       7,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   122,
       5,     7,     5,     7,   153,     7,     7,     7,     4,     7,
       7,     4,     7,     7,    82,     4,     4,     4,     4,     3,
     566,     6,     3,     6,     6,   153,     3,     6,     3,   153,
       6,     3,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   153,     3,     6,     6,     3,     6,     3,     3,
       8,     4,     4,     4,     4,   154,   156,   154,   156,   154,
       4,     4,   154,   154,   154,     4,   154,   154,     4,   154,
     154,   154,     4,     4,     8,   154,     6,     4,     4,     8,
       8,     4,     4,     7,     4,   765,   768,   153,   768,   765,
     154,   771,     4,     4,   774,   777,   153,   777,   774,   768,
     153,   777,   768,   774,   768,   153,   153,   787,   777,   768,
       4,   777,   771,   777,   555,   774,   774,   153,   777,   156,
     550,   153,   153,   803,   153,   153,   338,   807,   153,   557,
     154,   154,   153,   765,   814,   780,   364,   817,   789,   783,
     820,   368,   796,   770,   803,   825,   787,   768,   807,   825,
     771,   768,   921,   774,   779,   814,   777,   420,   817,   382,
      77,   820,   773,   776,   771,   412,   825,   816,   768,   774,
     817,   807,   417,   819,   814,   385,   578,   777,   436,   392,
     822,   820,   803,   402,   803,   551,   807,   573,   826,   939,
     952,   969,    -1,   814,    -1,   439,   817,    -1,    -1,   820,
      -1,    -1,    -1,    -1,   825,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   814,    -1,    -1,   817,    -1,    -1,
     820,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   921,
      -1,   921,    -1,    -1,    -1,   921,    -1,    -1,    -1,    -1,
      -1,    -1,   921,    -1,    -1,   921,    -1,   921,    -1,   939,
      -1,    -1,   921,   939,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     939,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     921,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   939,    -1,
      -1,   921
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
       7,   340,     7,   259,     7,   447,     7,   482,   181,   176,
     190,   196,   207,   284,   359,   375,   392,   311,   317,   341,
     260,   448,   483,   173,   182,   183,   153,   178,   179,    10,
     127,   136,   137,   138,   153,   188,   191,   192,   193,   474,
     476,   478,   480,    11,    14,    15,    31,    32,    33,    34,
      35,    36,    37,    38,    56,    57,    67,    68,    69,    70,
      71,    83,    86,    93,   101,   102,   105,   188,   197,   198,
     199,   200,   201,   202,   203,   204,   213,   215,   239,   245,
     251,   253,   267,   277,   300,   308,   334,   364,   366,   414,
     424,   436,   437,   445,    12,    13,   188,   208,   209,   210,
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
     116,   117,   118,   119,   188,   364,   366,   449,   450,   451,
     452,   454,   456,   457,   459,   460,   461,   464,   466,   467,
     468,   469,   472,   128,   484,   485,   486,     6,     3,     4,
       8,     3,   194,   481,   475,   477,   479,     4,     3,     8,
     205,   214,   216,     4,     4,     4,     4,     4,   278,   309,
     335,   365,   367,   301,   240,   252,   246,   415,   254,   268,
     425,     4,   438,   446,     3,     8,   211,     4,     3,     8,
     417,   353,   369,   288,   290,   292,     4,     4,   296,   294,
     386,   411,     3,     8,   363,     3,     8,   379,     4,   382,
       4,     4,     3,     8,   409,   397,   399,   401,   403,   405,
     407,     8,     3,     8,   325,   230,     4,   329,   327,   332,
       4,     8,     3,   347,     4,     4,     8,     3,   264,   266,
       3,     8,     4,   453,   455,     4,   458,     4,     4,   462,
     465,     4,     4,     4,   470,   473,     3,     8,   487,     3,
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
       4,   156,   156,   156,     4,     4,   450,     4,   485,     4,
       7,     7,   173,   173,   173,     7,     7,     7,     5,     5,
       5,   175,   177,   153,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   184,   423,     8,     3,     5,
       5,   153,   153,   153,    64,    65,    66,   297,   153,     5,
       7,   153,   153,   153,   184,   184,   184,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   173,   153,
     153,   153,   120,   121,   463,   122,   123,   124,   125,   126,
     156,   471,   153,     5,   173,   197,   484,   208,    16,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,   188,
     217,   218,   219,   222,   224,   226,   228,   229,   231,   232,
     233,   234,   235,   237,   217,     7,   279,   280,   281,     7,
     312,   313,   314,     7,   336,   337,   338,     7,   302,   303,
     304,    77,   153,   241,   242,   243,   244,   182,    78,    80,
     243,   247,   248,   249,   250,   293,   416,     7,   255,   256,
     257,    87,    88,    89,    90,    91,    92,   269,   270,   271,
     272,   273,   274,   275,   276,    16,    97,    98,    99,   100,
     188,   231,   364,   366,   426,   427,   428,   431,   432,   434,
     435,   103,   104,   188,   364,   366,   439,   440,   441,   443,
     449,   185,     4,   420,     7,   354,   355,   356,     7,   370,
     371,   372,     7,   387,   388,   389,    82,   412,     7,   488,
     489,     8,     8,     8,   220,   223,   225,   227,     4,     4,
       4,     4,     4,   236,   238,     3,     8,     8,   282,     6,
       3,   315,     6,     3,   339,     6,     3,   305,     6,     3,
       3,     6,     6,     3,     6,     3,     6,   258,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   429,   433,
       4,     4,     4,     3,     8,   442,   444,     3,     8,     8,
     153,   186,   187,   153,   357,     6,     3,   373,     6,     3,
     390,     6,     3,   413,     8,   490,     3,     6,     4,     4,
       4,     4,   154,   156,   154,   156,   154,     4,     4,   218,
     285,   281,   318,   314,   342,   338,   188,   199,   200,   201,
     202,   229,   277,   289,   291,   293,   295,   299,   306,   307,
     334,   364,   366,   410,   304,   242,   248,   293,   261,   257,
     154,   154,   154,   154,   154,   154,   270,     4,     4,   154,
     154,   154,   427,     4,     4,   440,     6,     3,   360,   356,
     376,   372,   393,   389,     4,   129,   131,   132,   188,   229,
     364,   366,   491,   492,   493,   494,   496,   489,    17,    18,
      19,    20,   221,   153,   153,   153,   153,   153,     8,     8,
       8,     3,     8,     8,    94,    95,    96,   430,   153,   153,
     153,   153,     8,     8,     8,   153,   497,     4,   495,     3,
       8,   307,     4,   154,     4,   492,     5,   153,     7,   498,
     499,   500,     3,     6,   130,   133,   134,   135,   501,   502,
     503,   505,   506,   507,   499,   504,     4,     4,     4,     3,
       8,     4,   156,   154,   154,   502,   153
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
     440,   442,   441,   444,   443,   446,   445,   448,   447,   449,
     449,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   451,   453,
     452,   455,   454,   456,   458,   457,   459,   460,   462,   461,
     463,   463,   465,   464,   466,   467,   468,   470,   469,   471,
     471,   471,   471,   471,   473,   472,   475,   474,   477,   476,
     479,   478,   481,   480,   483,   482,   484,   484,   485,   487,
     486,   488,   488,   490,   489,   491,   491,   492,   492,   492,
     492,   492,   492,   492,   493,   495,   494,   497,   496,   498,
     498,   500,   499,   501,   501,   502,   502,   502,   502,   504,
     503,   505,   506,   507
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
       1,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     3,     3,     3
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
  "socket_name", "$@95", "dhcp_ddns", "$@96", "sub_dhcp_ddns", "$@97",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@98", "server_ip", "$@99", "server_port",
  "sender_ip", "$@100", "sender_port", "max_queue_size", "ncr_protocol",
  "$@101", "ncr_protocol_value", "ncr_format", "$@102",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@103", "replace_client_name_value",
  "generated_prefix", "$@104", "dhcp4_json_object", "$@105",
  "dhcpddns_json_object", "$@106", "control_agent_json_object", "$@107",
  "logging_object", "$@108", "sub_logging", "$@109", "logging_params",
  "logging_param", "loggers", "$@110", "loggers_entries", "logger_entry",
  "$@111", "logger_params", "logger_param", "debuglevel", "severity",
  "$@112", "output_options_list", "$@113", "output_options_list_content",
  "output_entry", "$@114", "output_params_list", "output_params", "output",
  "$@115", "flush", "maxsize", "maxver", YY_NULLPTR
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
    1311,  1312,  1315,  1315,  1323,  1323,  1342,  1342,  1360,  1360,
    1372,  1373,  1376,  1377,  1380,  1380,  1392,  1392,  1404,  1405,
    1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1419,
    1419,  1427,  1432,  1432,  1440,  1445,  1453,  1453,  1463,  1464,
    1467,  1468,  1471,  1471,  1480,  1480,  1489,  1490,  1493,  1494,
    1498,  1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,
    1508,  1511,  1511,  1521,  1521,  1531,  1531,  1539,  1539,  1547,
    1547,  1555,  1555,  1563,  1563,  1576,  1576,  1586,  1586,  1597,
    1597,  1607,  1608,  1611,  1611,  1621,  1622,  1625,  1626,  1629,
    1630,  1631,  1632,  1633,  1634,  1637,  1639,  1639,  1650,  1650,
    1662,  1663,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,
    1674,  1677,  1677,  1684,  1685,  1686,  1689,  1694,  1694,  1702,
    1707,  1714,  1721,  1721,  1731,  1732,  1735,  1736,  1737,  1738,
    1739,  1742,  1742,  1750,  1750,  1760,  1760,  1772,  1772,  1782,
    1783,  1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,
    1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1805,  1810,
    1810,  1818,  1818,  1826,  1831,  1831,  1839,  1844,  1849,  1849,
    1857,  1858,  1861,  1861,  1869,  1874,  1879,  1884,  1884,  1892,
    1895,  1898,  1901,  1904,  1910,  1910,  1920,  1920,  1927,  1927,
    1934,  1934,  1947,  1947,  1957,  1957,  1968,  1969,  1973,  1977,
    1977,  1989,  1990,  1994,  1994,  2002,  2003,  2006,  2007,  2008,
    2009,  2010,  2011,  2012,  2015,  2020,  2020,  2028,  2028,  2038,
    2039,  2042,  2042,  2050,  2051,  2054,  2055,  2056,  2057,  2060,
    2060,  2068,  2073,  2078
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
#line 4574 "dhcp6_parser.cc" // lalr1.cc:1167
#line 2083 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
