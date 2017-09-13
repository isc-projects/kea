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
      case 168: // value
      case 172: // map_value
      case 216: // db_type
      case 292: // hr_mode
      case 421: // duid_type
      case 454: // ncr_protocol_value
      case 462: // replace_client_name_value
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
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 168: // value
      case 172: // map_value
      case 216: // db_type
      case 292: // hr_mode
      case 421: // duid_type
      case 454: // ncr_protocol_value
      case 462: // replace_client_name_value
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
            case 150: // "constant string"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 364 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 151: // "integer"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 371 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 152: // "floating point"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 378 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 153: // "boolean"

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< bool > (); }
#line 385 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 168: // value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 392 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 172: // map_value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 399 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 216: // db_type

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 406 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 292: // hr_mode

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 413 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 421: // duid_type

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 420 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 454: // ncr_protocol_value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 427 "dhcp6_parser.cc" // lalr1.cc:636
        break;

      case 462: // replace_client_name_value

#line 226 "dhcp6_parser.yy" // lalr1.cc:636
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
      case 168: // value
      case 172: // map_value
      case 216: // db_type
      case 292: // hr_mode
      case 421: // duid_type
      case 454: // ncr_protocol_value
      case 462: // replace_client_name_value
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
#line 235 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 680 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 236 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.CONFIG; }
#line 686 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 237 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP6; }
#line 692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 238 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 698 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 239 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.SUBNET6; }
#line 704 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 240 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.POOLS; }
#line 710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 241 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 716 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 242 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 722 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 243 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 244 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 734 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 245 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 740 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 246 "dhcp6_parser.yy" // lalr1.cc:859
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 254 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 255 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 256 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 764 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 257 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 770 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 258 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 776 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 259 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 260 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 788 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 268 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 808 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 818 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 279 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 286 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 833 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 290 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 300 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
}
#line 860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 308 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 312 "dhcp6_parser.yy" // lalr1.cc:859
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 878 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 319 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // List parsing about to start
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 321 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 895 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 330 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 904 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 334 "dhcp6_parser.yy" // lalr1.cc:859
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 913 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 345 "dhcp6_parser.yy" // lalr1.cc:859
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 924 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 355 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 935 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 360 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 380 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 958 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 970 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 397 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 980 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 401 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 988 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 436 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 997 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1006 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 446 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1015 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 451 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1024 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 456 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1033 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 461 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 466 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 471 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 475 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1071 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 487 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 492 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 503 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 508 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 513 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 518 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 542 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 544 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 549 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1163 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 550 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 551 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1175 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 552 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1181 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 555 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 557 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 563 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 565 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1217 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 573 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1235 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 140:
#line 579 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1244 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 141:
#line 584 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 142:
#line 586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1262 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 143:
#line 592 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 144:
#line 597 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1280 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 145:
#line 602 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1289 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 146:
#line 607 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1298 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 147:
#line 612 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 148:
#line 614 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1316 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 149:
#line 620 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 150:
#line 622 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1334 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 151:
#line 629 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1345 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 152:
#line 634 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 157:
#line 647 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1363 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 158:
#line 652 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1372 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 159:
#line 657 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 160:
#line 662 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1392 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 166:
#line 676 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 167:
#line 681 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 168:
#line 688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1421 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 169:
#line 693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 170:
#line 698 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 171:
#line 703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 176:
#line 716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1460 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 177:
#line 720 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 178:
#line 724 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1478 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 179:
#line 728 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 185:
#line 741 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 186:
#line 743 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 187:
#line 749 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 188:
#line 751 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 189:
#line 757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1532 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 190:
#line 762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 199:
#line 779 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1550 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 200:
#line 784 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 201:
#line 789 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 202:
#line 794 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1577 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 203:
#line 799 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1586 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 204:
#line 804 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 205:
#line 812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1606 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 206:
#line 817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1615 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 211:
#line 837 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 212:
#line 841 "dhcp6_parser.yy" // lalr1.cc:859
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
    ctx.stack_.pop_back();
}
#line 1648 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 213:
#line 860 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1658 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 214:
#line 864 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1666 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 234:
#line 893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 235:
#line 895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 236:
#line 901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1692 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 237:
#line 903 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 238:
#line 909 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 239:
#line 911 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 240:
#line 917 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.CLIENT_CLASS);
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 241:
#line 919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 242:
#line 925 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1746 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 243:
#line 927 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 244:
#line 932 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1761 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 245:
#line 933 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1767 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 246:
#line 934 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1773 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 247:
#line 937 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 248:
#line 942 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 249:
#line 950 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1802 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 250:
#line 955 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 255:
#line 970 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 256:
#line 974 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1829 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 273:
#line 1002 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 1840 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 274:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1849 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 279:
#line 1024 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1859 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 280:
#line 1028 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 1867 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 281:
#line 1035 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 282:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 1885 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 296:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 1894 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 298:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1902 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 299:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 1912 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 300:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1920 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 301:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 1930 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 302:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1938 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 303:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 305:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1956 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 306:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 1966 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 307:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 308:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 309:
#line 1120 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 314:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 315:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 316:
#line 1150 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 317:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 330:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 331:
#line 1186 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 334:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2058 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 335:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2067 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 336:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2078 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 337:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2087 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 342:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2097 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 343:
#line 1233 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 344:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2115 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 345:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2123 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 352:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2131 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 353:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2141 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 354:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 355:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("user-context", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 356:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2169 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 357:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2178 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 362:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 363:
#line 1297 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2196 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 364:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2206 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 365:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 376:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2222 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 377:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 378:
#line 1331 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 379:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 380:
#line 1338 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 381:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2268 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 382:
#line 1349 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 383:
#line 1357 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2288 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 384:
#line 1362 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2297 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 389:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2307 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 390:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2315 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 391:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 392:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2333 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 406:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 407:
#line 1416 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 408:
#line 1421 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 409:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2373 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 410:
#line 1431 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2381 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 411:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2391 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 412:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2399 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 413:
#line 1441 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 414:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2417 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 415:
#line 1449 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 416:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 417:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2445 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 418:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 419:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2465 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 420:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 421:
#line 1481 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 422:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2493 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 423:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr ip(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
}
#line 2503 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 424:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 425:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 428:
#line 1511 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2533 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 429:
#line 1515 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 2541 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 439:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2549 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 440:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2559 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 441:
#line 1546 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 442:
#line 1551 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2579 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 452:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 453:
#line 1571 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 454:
#line 1576 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2602 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 455:
#line 1577 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2608 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 456:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2614 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 457:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2623 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 458:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2631 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 459:
#line 1588 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 460:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 461:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 462:
#line 1606 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2668 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 463:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 464:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 469:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 470:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 2706 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 471:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 472:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 473:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 2735 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 474:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2744 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 475:
#line 1659 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 476:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:859
    {
    // parsing completed
}
#line 2762 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 494:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 495:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 496:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 497:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 498:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 2807 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 499:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 500:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2824 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 501:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 502:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 503:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 2852 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 504:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 2860 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 505:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 506:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 2875 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 507:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:859
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 2881 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 508:
#line 1744 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 2889 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 509:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 2899 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 510:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 2908 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 511:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 2917 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 512:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 2926 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 513:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 2934 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 514:
#line 1769 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 515:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location))); 
      }
#line 2951 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 516:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 2959 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 517:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 2967 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 518:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 2975 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 519:
#line 1787 "dhcp6_parser.yy" // lalr1.cc:859
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 2984 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 520:
#line 1793 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2992 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 521:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 522:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3010 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 523:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3019 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 524:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 525:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 526:
#line 1817 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 527:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 528:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3064 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 529:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3073 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 533:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3084 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 534:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 537:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 538:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3111 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 546:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3120 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 547:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3128 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 548:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3138 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 549:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3149 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 550:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3158 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 553:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3168 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 554:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.stack_.pop_back();
}
#line 3176 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 561:
#line 1933 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 562:
#line 1935 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 563:
#line 1941 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3203 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 564:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3212 "dhcp6_parser.cc" // lalr1.cc:859
    break;

  case 565:
#line 1951 "dhcp6_parser.yy" // lalr1.cc:859
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3221 "dhcp6_parser.cc" // lalr1.cc:859
    break;


#line 3225 "dhcp6_parser.cc" // lalr1.cc:859
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


  const short int Dhcp6Parser::yypact_ninf_ = -702;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short int
  Dhcp6Parser::yypact_[] =
  {
     202,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,    40,    18,    70,    78,   120,   122,   141,
     147,   175,   183,   211,   219,   223,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
      18,  -120,    23,    30,    46,    22,     1,    35,   145,    62,
     159,   -37,   140,  -702,    36,    72,   106,   154,   207,  -702,
    -702,  -702,  -702,  -702,   228,  -702,    66,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,   230,   274,   275,   297,
     299,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,   306,  -702,  -702,  -702,    68,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,   312,   103,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,   328,   331,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,   125,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,   144,  -702,  -702,  -702,  -702,   333,  -702,   334,   358,
    -702,  -702,  -702,   171,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   284,
     360,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,   361,  -702,  -702,  -702,   362,  -702,  -702,   356,   364,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,   365,   366,  -702,  -702,  -702,  -702,   363,   369,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   201,
    -702,  -702,  -702,   370,  -702,  -702,   371,  -702,   372,   373,
    -702,  -702,   374,   375,   376,  -702,  -702,  -702,   203,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,    18,    18,  -702,   218,   377,
     378,   379,   380,   381,  -702,    23,  -702,   382,   383,   384,
     222,   238,   239,   240,   241,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   253,   401,   402,    30,
    -702,   403,   255,    46,  -702,    79,   405,   406,   407,   408,
     409,   265,   261,   411,   413,   414,   415,    22,  -702,   419,
     420,     1,  -702,   421,   276,   422,   277,   280,    35,  -702,
     425,   426,   428,   429,   430,   431,   432,  -702,   145,   433,
     434,   289,   435,   437,   438,   291,  -702,    62,   439,   292,
     293,  -702,   159,   443,   444,     9,  -702,   296,   446,   449,
     303,   453,   307,   308,   456,   457,   313,   314,   315,   458,
     460,   140,  -702,  -702,  -702,   465,   464,   466,    18,    18,
      18,  -702,   468,   469,   470,  -702,  -702,  -702,  -702,  -702,
     467,   473,   474,   475,   476,   477,   478,   479,   481,   480,
     482,  -702,   483,   484,  -702,   487,  -702,  -702,  -702,  -702,
    -702,  -702,   485,   491,  -702,  -702,  -702,   490,   492,   338,
     346,   348,  -702,  -702,    56,   349,   495,   496,  -702,   352,
     497,  -702,   355,  -702,   357,  -702,  -702,  -702,   487,   487,
     487,   359,   367,   385,   386,  -702,   387,   388,  -702,   400,
     404,   410,  -702,  -702,   412,  -702,  -702,  -702,   416,    18,
    -702,  -702,   417,   418,  -702,   423,  -702,  -702,    16,   424,
    -702,  -702,  -702,   115,   427,  -702,    18,    30,   436,  -702,
    -702,  -702,    46,   116,   116,   499,   501,   503,   504,   -45,
      18,    99,    42,   505,   173,    27,   139,   140,  -702,  -702,
     509,  -702,    79,   507,   508,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,   512,   440,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
     225,  -702,   262,  -702,  -702,   264,  -702,  -702,  -702,  -702,
     516,   518,   519,   520,   521,  -702,  -702,  -702,   266,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,   268,  -702,   510,   523,  -702,  -702,   522,   524,
    -702,  -702,   525,   526,  -702,  -702,   527,   529,  -702,  -702,
    -702,    45,  -702,  -702,  -702,   528,  -702,  -702,  -702,   150,
    -702,  -702,  -702,  -702,   178,  -702,   533,   537,  -702,   538,
     539,   540,   542,   543,   544,   272,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,   545,   547,   548,  -702,  -702,
     278,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   279,
    -702,  -702,  -702,   290,   441,   442,  -702,  -702,   535,   550,
    -702,  -702,   549,   553,  -702,  -702,   551,   555,  -702,  -702,
     556,  -702,   557,   436,  -702,  -702,   561,   565,   566,   567,
     445,   447,   448,   450,   451,   568,   570,   116,  -702,  -702,
      22,  -702,   499,    62,  -702,   501,   159,  -702,   503,   155,
    -702,   504,   -45,  -702,  -702,    99,  -702,    42,  -702,   -37,
    -702,   505,   454,   455,   459,   461,   462,   463,   173,  -702,
     571,   572,   471,   472,   486,    27,  -702,   574,   575,   139,
    -702,  -702,  -702,   576,   577,  -702,     1,  -702,   507,    35,
    -702,   508,   145,  -702,   512,   579,  -702,   554,  -702,   335,
     488,   489,   493,  -702,  -702,  -702,  -702,  -702,   494,   498,
    -702,   309,  -702,   573,  -702,   578,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   310,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,   311,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,   263,   500,  -702,  -702,
    -702,  -702,   502,   513,  -702,  -702,   534,   319,  -702,   320,
    -702,   580,  -702,   536,   582,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,   155,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,   288,  -702,  -702,    77,   582,  -702,
    -702,   581,  -702,  -702,  -702,   323,  -702,  -702,  -702,  -702,
    -702,   583,   511,   586,    77,  -702,   588,  -702,   541,  -702,
     587,  -702,  -702,   327,  -702,    63,   587,  -702,  -702,   591,
     593,   594,   326,  -702,  -702,  -702,  -702,  -702,  -702,   597,
     530,   546,   552,    63,  -702,   558,  -702,  -702,  -702,  -702,
    -702
  };

  const unsigned short int
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    41,    34,    30,
      29,    26,    27,    28,    33,     3,    31,    32,    54,     5,
      66,     7,   100,     9,   213,    11,   344,    13,   364,    15,
     391,    17,   281,    19,   316,    21,   178,    23,   475,    25,
      43,    37,     0,     0,     0,     0,     0,     0,   393,   283,
     318,     0,     0,    45,     0,    44,     0,     0,    38,    64,
     528,   522,   524,   526,     0,    63,     0,    56,    58,    60,
      61,    62,    59,    98,   109,   111,     0,     0,     0,     0,
       0,   205,   273,   308,   249,   151,   168,   159,   424,   170,
     189,   441,     0,   463,   473,    92,     0,    68,    70,    71,
      72,    73,    74,    77,    78,    79,    80,    82,    81,    86,
      87,    75,    76,    84,    85,    83,    88,    89,    90,    91,
     106,     0,     0,   102,   104,   105,   428,   336,   356,   234,
     236,   238,     0,     0,   242,   240,   383,   420,   233,   217,
     218,   219,   220,     0,   215,   224,   225,   226,   229,   231,
     227,   228,   221,   222,   223,   230,   232,   352,   354,   351,
     349,     0,   346,   348,   350,   376,     0,   379,     0,     0,
     375,   371,   374,     0,   366,   368,   369,   372,   373,   370,
     418,   406,   408,   410,   412,   414,   416,   405,   404,     0,
     394,   395,   399,   400,   397,   401,   402,   403,   398,   298,
     141,     0,   302,   300,   305,     0,   294,   295,     0,   284,
     285,   287,   297,   288,   289,   290,   304,   291,   292,   293,
     330,     0,     0,   328,   329,   332,   333,     0,   319,   320,
     322,   323,   324,   325,   326,   327,   185,   187,   182,     0,
     180,   183,   184,     0,   495,   497,     0,   500,     0,     0,
     504,   508,     0,     0,     0,   513,   520,   493,     0,   477,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,    42,     0,     0,    35,     0,     0,
       0,     0,     0,     0,    53,     0,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,   101,   430,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   214,     0,
       0,     0,   345,     0,     0,     0,     0,     0,     0,   365,
       0,     0,     0,     0,     0,     0,     0,   392,     0,     0,
       0,     0,     0,     0,     0,     0,   282,     0,     0,     0,
       0,   317,     0,     0,     0,     0,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   476,    46,    39,     0,     0,     0,     0,     0,
       0,    57,     0,     0,     0,    93,    94,    95,    96,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   462,     0,     0,    69,     0,   108,   103,   439,   437,
     438,   436,     0,   431,   432,   434,   435,     0,     0,     0,
       0,     0,   247,   248,     0,     0,     0,     0,   216,     0,
       0,   347,     0,   378,     0,   381,   382,   367,     0,     0,
       0,     0,     0,     0,     0,   396,     0,     0,   296,     0,
       0,     0,   307,   286,     0,   334,   335,   321,     0,     0,
     181,   494,     0,     0,   499,     0,   502,   503,     0,     0,
     510,   511,   512,     0,     0,   478,     0,     0,     0,   523,
     525,   527,     0,     0,     0,   207,   275,   310,   251,     0,
      43,     0,     0,   172,     0,     0,     0,     0,    47,   107,
       0,   429,     0,   338,   358,   235,   237,   239,   244,   245,
     246,   243,   241,   385,     0,   353,    36,   355,   377,   380,
     419,   407,   409,   411,   413,   415,   417,   299,   142,   303,
     301,   306,   331,   186,   188,   496,   498,   501,   506,   507,
     505,   509,   515,   516,   517,   518,   519,   514,   521,    40,
       0,   533,     0,   530,   532,     0,   128,   134,   136,   138,
       0,     0,     0,     0,     0,   147,   149,   127,     0,   113,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   211,     0,   208,   209,   279,     0,   276,
     277,   314,     0,   311,   312,   255,     0,   252,   253,   157,
     158,     0,   153,   155,   156,     0,   166,   167,   163,     0,
     161,   164,   165,   426,     0,   176,     0,   173,   174,     0,
       0,     0,     0,     0,     0,     0,   191,   193,   194,   195,
     196,   197,   198,   452,   458,     0,     0,     0,   451,   450,
       0,   443,   445,   448,   446,   447,   449,   469,   471,     0,
     465,   467,   468,     0,    49,     0,   433,   342,     0,   339,
     340,   362,     0,   359,   360,   389,     0,   386,   387,   422,
       0,    65,     0,     0,   529,    99,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,   112,
       0,   206,     0,   283,   274,     0,   318,   309,     0,     0,
     250,     0,     0,   152,   169,     0,   160,     0,   425,     0,
     171,     0,     0,     0,     0,     0,     0,     0,     0,   190,
       0,     0,     0,     0,     0,     0,   442,     0,     0,     0,
     464,   474,    51,     0,    50,   440,     0,   337,     0,     0,
     357,     0,   393,   384,     0,     0,   421,     0,   531,     0,
       0,     0,     0,   140,   143,   144,   145,   146,     0,     0,
     114,     0,   210,     0,   278,     0,   313,   272,   269,   271,
     263,   264,   259,   260,   261,   262,   267,   270,     0,   257,
     265,   266,   268,   254,   154,   162,   427,     0,   175,   199,
     200,   201,   202,   203,   204,   192,     0,     0,   457,   460,
     461,   444,     0,     0,   466,    48,     0,     0,   341,     0,
     361,     0,   388,     0,     0,   130,   131,   132,   133,   129,
     135,   137,   139,   148,   150,   212,   280,   315,     0,   256,
     177,   454,   455,   456,   453,   459,   470,   472,    52,   343,
     363,   390,   423,   537,     0,   535,   258,     0,     0,   534,
     549,     0,   547,   545,   541,     0,   539,   543,   544,   542,
     536,     0,     0,     0,     0,   538,     0,   546,     0,   540,
       0,   548,   553,     0,   551,     0,     0,   550,   561,     0,
       0,     0,     0,   555,   557,   558,   559,   560,   552,     0,
       0,     0,     0,     0,   554,     0,   563,   564,   565,   556,
     562
  };

  const short int
  Dhcp6Parser::yypgoto_[] =
  {
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,    12,  -702,   124,  -702,  -702,  -702,
    -702,  -702,  -702,    10,  -702,  -109,  -702,  -702,  -702,   -62,
    -702,  -702,  -702,   302,  -702,  -702,  -702,  -702,    97,   282,
     -64,   -63,   -50,   -48,  -702,  -702,  -702,  -702,  -702,    96,
     283,  -702,  -702,  -702,  -702,  -702,  -702,  -702,    95,  -102,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
     -58,  -702,  -511,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -115,  -499,  -702,  -702,  -702,  -702,  -117,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -122,  -702,
    -702,  -702,  -119,   236,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -124,  -702,  -702,  -702,  -702,  -702,  -702,  -701,  -702,
    -702,  -702,   -97,  -702,  -702,  -702,   -94,   281,  -702,  -702,
    -697,  -702,  -695,  -702,  -506,  -702,  -694,  -702,  -702,  -702,
    -693,  -702,  -702,  -702,  -702,  -104,  -702,  -702,  -229,  -702,
    -702,  -702,  -702,   -95,  -702,  -702,  -702,   -92,  -702,   256,
    -702,   -57,  -702,  -702,  -702,  -702,  -702,   -46,  -702,  -702,
    -702,  -702,  -702,   -47,  -702,  -702,  -702,   -96,  -702,  -702,
    -702,   -91,  -702,   252,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -132,  -702,  -702,  -702,  -126,
     294,  -702,  -702,   -56,  -702,  -702,  -702,  -702,  -702,  -130,
    -702,  -702,  -702,  -127,   295,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -128,  -702,  -702,  -702,
    -125,  -702,   286,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -692,  -702,  -702,
    -702,  -691,  -702,  -702,  -702,  -702,  -702,   117,  -702,  -702,
    -702,  -702,  -702,  -702,   -81,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -108,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,   133,   287,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
    -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,  -702,
     -28,  -702,  -702,  -702,  -202,  -702,  -702,  -216,  -702,  -702,
    -702,  -702,  -702,  -702,  -221,  -702,  -702,  -236,  -702,  -702,
    -702,  -702,  -702
  };

  const short int
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    73,    35,    36,    61,   547,    77,
      78,    37,    60,    74,    75,   529,   684,   763,   764,   115,
      39,    62,    86,    87,    88,   299,    41,    63,   116,   117,
     118,   119,   120,   121,   122,   123,   307,    43,    64,   142,
     143,   144,   331,   145,   124,   308,   125,   309,   598,   599,
     600,   706,   849,   601,   707,   602,   708,   603,   709,   604,
     227,   370,   606,   607,   608,   609,   610,   715,   611,   716,
     126,   319,   631,   632,   633,   634,   127,   321,   639,   640,
     641,   642,   128,   320,   129,   323,   646,   647,   648,   739,
      57,    71,   259,   260,   261,   383,   262,   384,   130,   324,
     655,   656,   657,   658,   659,   660,   661,   662,   131,   315,
     614,   615,   616,   720,    45,    65,   163,   164,   165,   338,
     166,   339,   167,   340,   168,   344,   169,   343,   541,   170,
     171,   132,   318,   626,   627,   628,   729,   808,   809,   133,
     316,   618,   619,   620,   723,    53,    69,   228,   229,   230,
     231,   232,   233,   234,   369,   235,   373,   236,   372,   237,
     238,   374,   239,   134,   317,   622,   623,   624,   726,    55,
      70,   247,   248,   249,   250,   251,   378,   252,   253,   254,
     255,   173,   336,   688,   689,   690,   766,    47,    66,   181,
     182,   183,   349,   184,   350,   174,   337,   692,   693,   694,
     769,    49,    67,   193,   194,   195,   353,   196,   197,   355,
     198,   199,   175,   345,   696,   697,   698,   772,    51,    68,
     209,   210,   211,   212,   361,   213,   362,   214,   363,   215,
     364,   216,   365,   217,   366,   218,   360,   176,   346,   700,
     775,   135,   322,   644,   335,   442,   443,   444,   445,   446,
     530,   136,   325,   670,   671,   672,   750,   864,   673,   674,
     751,   675,   676,   137,   138,   327,   679,   680,   681,   757,
     682,   758,   139,   328,    59,    72,   278,   279,   280,   281,
     388,   282,   389,   283,   284,   391,   285,   286,   287,   394,
     570,   288,   395,   289,   290,   291,   292,   399,   577,   293,
     400,    89,   301,    90,   302,    91,   303,    92,   300,   582,
     583,   584,   702,   874,   875,   877,   885,   886,   887,   888,
     893,   889,   891,   903,   904,   905,   912,   913,   914,   919,
     915,   916,   917
  };

  const unsigned short int
  Dhcp6Parser::yytable_[] =
  {
      85,   159,   160,   158,   179,   190,   207,   226,   243,   258,
     277,   192,   244,   245,   669,   161,   643,   162,   172,   180,
     191,   208,   638,    27,   246,    28,    34,    29,   803,   146,
      76,   629,   804,    79,   805,   806,   807,   811,   812,   103,
      26,    93,   294,   663,    94,    95,   256,   257,   732,   146,
     177,   733,   591,    96,    97,    98,    99,   178,   140,   141,
     103,    96,    97,    98,    99,   100,   101,   102,   103,   305,
     147,   329,   148,   103,   306,   295,   330,    38,   219,   149,
     150,   151,   152,   153,   154,    40,   185,   186,   187,   188,
     189,   178,   256,   257,   155,   156,   104,   105,   106,   107,
     108,   220,   157,   221,   222,   630,   333,   223,   224,   225,
     296,   334,   109,    84,   155,   110,   220,   103,   220,   538,
     539,   540,   111,   664,   665,   666,   667,    42,   347,    44,
     112,   113,   586,   348,   114,   568,   569,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   351,    46,    80,
     438,    84,   352,   735,    48,   220,   736,   803,    81,    82,
      83,   804,   297,   805,   806,   807,   811,   812,    30,    31,
      32,    33,    84,    84,   358,   629,   636,    84,   637,   359,
      84,   737,    50,   103,   738,    84,    96,    97,    98,    99,
      52,   101,   908,   103,   220,   909,   910,   911,   220,   240,
     221,   222,   241,   242,   385,   880,   401,   881,   882,   386,
     298,   402,    84,   150,   151,   200,   153,   154,    54,   201,
     202,   203,   204,   205,   206,   108,    56,    84,   329,    84,
      58,   816,   304,   701,   310,   157,   638,   572,   573,   574,
     575,   677,   678,    85,   669,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   649,
     650,   651,   652,   653,   654,   703,    84,   333,   576,   717,
     704,   717,   705,   439,   718,   748,   719,   440,   311,   312,
     749,   755,   759,   159,   160,   158,   756,   760,   441,   179,
      84,   878,   367,   401,   879,    84,   190,   161,   761,   162,
     172,   313,   192,   314,   180,    84,   207,   403,   404,    84,
     326,   191,   347,   858,   385,   226,   332,   855,   859,   860,
     243,   208,   351,   358,   244,   245,   894,   869,   870,   923,
     906,   895,   341,   907,   924,   342,   246,   354,   356,   277,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,   845,   846,   847,   848,   861,   862,   863,   550,
     551,   552,   357,   368,   376,   371,   375,   377,   405,   379,
     380,   381,   382,   415,   387,   390,   392,   393,   396,   397,
     398,   406,   407,   408,   409,   410,   412,   413,   414,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   435,   436,   447,
     448,   449,   450,   451,   453,   454,   452,   455,   456,   457,
     509,   510,   511,   459,   460,   462,   464,   463,   465,   468,
     469,   466,   470,   471,   472,   473,   474,   476,   477,   479,
     478,   480,   481,   484,   482,   485,   486,   488,   489,   491,
     492,   597,   597,   493,   494,   605,   605,   495,   496,   497,
     498,   499,   503,   668,   504,   277,   500,   501,   502,   506,
     439,   507,   515,   508,   440,   512,   513,   514,   516,   517,
     518,   519,   520,   521,   522,   441,   523,   524,   535,   525,
     526,   527,   528,   531,   532,   533,   536,   534,   537,   542,
     543,   564,   545,   544,    28,   548,   613,   549,   617,   553,
     621,   625,   645,   685,   687,   691,   721,   554,   579,   695,
     710,   699,   711,   712,   713,   714,   722,   725,   724,   728,
     635,   727,   731,   730,   734,   555,   556,   557,   558,   740,
     741,   767,   742,   743,   744,   571,   745,   746,   747,   752,
     559,   753,   754,   768,   560,   770,   771,   773,   774,   844,
     561,   777,   562,   581,   776,   779,   563,   565,   566,   780,
     781,   782,   788,   567,   789,   826,   827,   578,   832,   833,
     836,   856,   835,   843,   546,   892,   857,   896,   871,   873,
     898,   762,   765,   900,   902,   920,   783,   921,   922,   785,
     784,   925,   787,   786,   580,   819,   820,   411,   585,   612,
     821,   434,   822,   823,   824,   790,   437,   814,   815,   818,
     817,   490,   828,   829,   825,   792,   791,   813,   458,   876,
     794,   793,   796,   483,   487,   795,   838,   830,   850,   851,
     837,   840,   839,   852,   853,   461,   842,   841,   854,   686,
     865,   834,   866,   467,   475,   597,   159,   160,   158,   605,
     683,   226,   897,   867,   243,   798,   799,   797,   244,   245,
     161,   802,   162,   172,   831,   778,   890,   258,   899,   800,
     246,   801,   810,   926,   868,   918,   872,   929,   505,     0,
       0,   901,     0,   668,     0,     0,     0,   927,     0,     0,
       0,     0,     0,   928,   179,     0,     0,   190,   930,     0,
     207,     0,     0,   192,     0,     0,     0,     0,     0,   180,
       0,     0,   191,     0,     0,   208,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   798,   799,   797,     0,     0,     0,
     802,     0,     0,     0,     0,     0,     0,     0,   800,     0,
     801,   810,     0,     0,     0,   883,     0,     0,     0,   884,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   883,     0,     0,     0,   884
  };

  const short int
  Dhcp6Parser::yycheck_[] =
  {
      62,    65,    65,    65,    66,    67,    68,    69,    70,    71,
      72,    67,    70,    70,   525,    65,   522,    65,    65,    66,
      67,    68,   521,     5,    70,     7,    14,     9,   729,     7,
     150,    76,   729,    10,   729,   729,   729,   729,   729,    38,
       0,    11,     6,    16,    14,    15,    83,    84,     3,     7,
      49,     6,    25,    31,    32,    33,    34,    56,    12,    13,
      38,    31,    32,    33,    34,    35,    36,    37,    38,     3,
      48,     3,    50,    38,     8,     3,     8,     7,    16,    57,
      58,    59,    60,    61,    62,     7,    51,    52,    53,    54,
      55,    56,    83,    84,    72,    73,    66,    67,    68,    69,
      70,    39,    80,    41,    42,   150,     3,    45,    46,    47,
       4,     8,    82,   150,    72,    85,    39,    38,    39,    63,
      64,    65,    92,    96,    97,    98,    99,     7,     3,     7,
     100,   101,    16,     8,   104,   119,   120,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     3,     7,   126,
      71,   150,     8,     3,     7,    39,     6,   858,   135,   136,
     137,   858,     8,   858,   858,   858,   858,   858,   150,   151,
     152,   153,   150,   150,     3,    76,    77,   150,    79,     8,
     150,     3,     7,    38,     6,   150,    31,    32,    33,    34,
       7,    36,   129,    38,    39,   132,   133,   134,    39,    40,
      41,    42,    43,    44,     3,   128,     3,   130,   131,     8,
       3,     8,   150,    58,    59,    70,    61,    62,     7,    74,
      75,    76,    77,    78,    79,    70,     7,   150,     3,   150,
       7,   737,     4,     8,     4,    80,   735,   122,   123,   124,
     125,   102,   103,   305,   755,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,    86,
      87,    88,    89,    90,    91,     3,   150,     3,   153,     3,
       8,     3,     8,   335,     8,     3,     8,   335,     4,     4,
       8,     3,     3,   347,   347,   347,     8,     8,   335,   351,
     150,     3,     8,     3,     6,   150,   358,   347,     8,   347,
     347,     4,   358,     4,   351,   150,   368,   295,   296,   150,
       4,   358,     3,     3,     3,   377,     4,     8,     8,     8,
     382,   368,     3,     3,   382,   382,     3,     8,     8,     3,
       3,     8,     4,     6,     8,     4,   382,     4,     4,   401,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,    17,    18,    19,    20,    93,    94,    95,   468,
     469,   470,     4,     3,     8,     4,     4,     3,   150,     4,
       4,     8,     3,   151,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   151,
     151,   151,   151,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   151,     4,     4,     4,   153,     4,
       4,     4,     4,     4,   153,     4,   151,     4,     4,     4,
     408,   409,   410,     4,     4,     4,     4,   151,   151,     4,
       4,   151,     4,     4,     4,     4,     4,     4,     4,     4,
     151,     4,     4,     4,   153,   153,   153,     4,     4,   153,
       4,   513,   514,     4,   151,   513,   514,     4,   151,   151,
       4,     4,     4,   525,     4,   527,   153,   153,   153,     4,
     532,     7,     5,     7,   532,     7,     7,     7,     5,     5,
       5,     5,     5,     5,     5,   532,     5,     7,   150,     7,
       7,     7,     5,     8,     3,     5,   150,     5,   150,   150,
       5,   489,   150,     7,     7,   150,     7,   150,     7,   150,
       7,     7,     7,     4,     7,     7,     6,   150,   506,     7,
       4,    81,     4,     4,     4,     4,     3,     3,     6,     3,
     520,     6,     3,     6,     6,   150,   150,   150,   150,     6,
       3,     6,     4,     4,     4,   121,     4,     4,     4,     4,
     150,     4,     4,     3,   150,     6,     3,     6,     3,     5,
     150,     4,   150,   127,     8,     4,   150,   150,   150,     4,
       4,     4,     4,   150,     4,     4,     4,   150,     4,     4,
       3,     8,     6,     4,   460,     4,     8,     4,     8,     7,
       4,   150,   150,     5,     7,     4,   151,     4,     4,   151,
     153,     4,   151,   153,   507,   151,   151,   305,   512,   514,
     151,   329,   151,   151,   151,   717,   333,   732,   735,   741,
     739,   385,   151,   151,   748,   722,   720,   731,   347,   858,
     725,   723,   728,   377,   382,   726,   768,   151,   150,   150,
     766,   771,   769,   150,   150,   351,   774,   772,   150,   532,
     150,   759,   150,   358,   368,   717,   720,   720,   720,   717,
     527,   723,   151,   150,   726,   729,   729,   729,   726,   726,
     720,   729,   720,   720,   755,   703,   878,   739,   894,   729,
     726,   729,   729,   153,   150,   906,   150,   923,   401,    -1,
      -1,   150,    -1,   755,    -1,    -1,    -1,   151,    -1,    -1,
      -1,    -1,    -1,   151,   766,    -1,    -1,   769,   150,    -1,
     772,    -1,    -1,   769,    -1,    -1,    -1,    -1,    -1,   766,
      -1,    -1,   769,    -1,    -1,   772,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   858,   858,   858,    -1,    -1,    -1,
     858,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   858,    -1,
     858,   858,    -1,    -1,    -1,   877,    -1,    -1,    -1,   877,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   894,    -1,    -1,    -1,   894
  };

  const unsigned short int
  Dhcp6Parser::yystos_[] =
  {
       0,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,     0,     5,     7,     9,
     150,   151,   152,   153,   168,   169,   170,   175,     7,   184,
       7,   190,     7,   201,     7,   278,     7,   351,     7,   365,
       7,   382,     7,   309,     7,   333,     7,   254,     7,   438,
     176,   171,   185,   191,   202,   279,   352,   366,   383,   310,
     334,   255,   439,   168,   177,   178,   150,   173,   174,    10,
     126,   135,   136,   137,   150,   183,   186,   187,   188,   465,
     467,   469,   471,    11,    14,    15,    31,    32,    33,    34,
      35,    36,    37,    38,    66,    67,    68,    69,    70,    82,
      85,    92,   100,   101,   104,   183,   192,   193,   194,   195,
     196,   197,   198,   199,   208,   210,   234,   240,   246,   248,
     262,   272,   295,   303,   327,   405,   415,   427,   428,   436,
      12,    13,   203,   204,   205,   207,     7,    48,    50,    57,
      58,    59,    60,    61,    62,    72,    73,    80,   183,   194,
     195,   196,   197,   280,   281,   282,   284,   286,   288,   290,
     293,   294,   327,   345,   359,   376,   401,    49,    56,   183,
     327,   353,   354,   355,   357,    51,    52,    53,    54,    55,
     183,   327,   357,   367,   368,   369,   371,   372,   374,   375,
      70,    74,    75,    76,    77,    78,    79,   183,   327,   384,
     385,   386,   387,   389,   391,   393,   395,   397,   399,    16,
      39,    41,    42,    45,    46,    47,   183,   224,   311,   312,
     313,   314,   315,   316,   317,   319,   321,   323,   324,   326,
      40,    43,    44,   183,   224,   315,   321,   335,   336,   337,
     338,   339,   341,   342,   343,   344,    83,    84,   183,   256,
     257,   258,   260,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   183,   440,   441,
     442,   443,   445,   447,   448,   450,   451,   452,   455,   457,
     458,   459,   460,   463,     6,     3,     4,     8,     3,   189,
     472,   466,   468,   470,     4,     3,     8,   200,   209,   211,
       4,     4,     4,     4,     4,   273,   304,   328,   296,   235,
     247,   241,   406,   249,   263,   416,     4,   429,   437,     3,
       8,   206,     4,     3,     8,   408,   346,   360,   283,   285,
     287,     4,     4,   291,   289,   377,   402,     3,     8,   356,
     358,     3,     8,   370,     4,   373,     4,     4,     3,     8,
     400,   388,   390,   392,   394,   396,   398,     8,     3,   318,
     225,     4,   322,   320,   325,     4,     8,     3,   340,     4,
       4,     8,     3,   259,   261,     3,     8,     4,   444,   446,
       4,   449,     4,     4,   453,   456,     4,     4,     4,   461,
     464,     3,     8,   168,   168,   150,     4,     4,     4,     4,
       4,   187,     4,     4,     4,   151,   151,   151,   151,   151,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   151,     4,     4,   193,     4,   153,   204,    71,   183,
     224,   327,   409,   410,   411,   412,   413,     4,     4,     4,
       4,     4,   151,   153,     4,     4,     4,     4,   281,     4,
       4,   354,     4,   151,     4,   151,   151,   368,     4,     4,
       4,     4,     4,     4,     4,   386,     4,     4,   151,     4,
       4,     4,   153,   313,     4,   153,   153,   337,     4,     4,
     257,   153,     4,     4,   151,     4,   151,   151,     4,     4,
     153,   153,   153,     4,     4,   441,     4,     7,     7,   168,
     168,   168,     7,     7,     7,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     7,     7,     7,     7,     5,   179,
     414,     8,     3,     5,     5,   150,   150,   150,    63,    64,
      65,   292,   150,     5,     7,   150,   170,   172,   150,   150,
     179,   179,   179,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   168,   150,   150,   150,   119,   120,
     454,   121,   122,   123,   124,   125,   153,   462,   150,   168,
     192,   127,   473,   474,   475,   203,    16,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,   183,   212,   213,
     214,   217,   219,   221,   223,   224,   226,   227,   228,   229,
     230,   232,   212,     7,   274,   275,   276,     7,   305,   306,
     307,     7,   329,   330,   331,     7,   297,   298,   299,    76,
     150,   236,   237,   238,   239,   177,    77,    79,   238,   242,
     243,   244,   245,   288,   407,     7,   250,   251,   252,    86,
      87,    88,    89,    90,    91,   264,   265,   266,   267,   268,
     269,   270,   271,    16,    96,    97,    98,    99,   183,   226,
     417,   418,   419,   422,   423,   425,   426,   102,   103,   430,
     431,   432,   434,   440,   180,     4,   411,     7,   347,   348,
     349,     7,   361,   362,   363,     7,   378,   379,   380,    81,
     403,     8,   476,     3,     8,     8,   215,   218,   220,   222,
       4,     4,     4,     4,     4,   231,   233,     3,     8,     8,
     277,     6,     3,   308,     6,     3,   332,     6,     3,   300,
       6,     3,     3,     6,     6,     3,     6,     3,     6,   253,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     420,   424,     4,     4,     4,     3,     8,   433,   435,     3,
       8,     8,   150,   181,   182,   150,   350,     6,     3,   364,
       6,     3,   381,     6,     3,   404,     8,     4,   474,     4,
       4,     4,     4,   151,   153,   151,   153,   151,     4,     4,
     213,   280,   276,   311,   307,   335,   331,   183,   194,   195,
     196,   197,   224,   272,   284,   286,   290,   294,   301,   302,
     327,   401,   405,   299,   237,   243,   288,   256,   252,   151,
     151,   151,   151,   151,   151,   265,     4,     4,   151,   151,
     151,   418,     4,     4,   431,     6,     3,   353,   349,   367,
     363,   384,   380,     4,     5,    17,    18,    19,    20,   216,
     150,   150,   150,   150,   150,     8,     8,     8,     3,     8,
       8,    93,    94,    95,   421,   150,   150,   150,   150,     8,
       8,     8,   150,     7,   477,   478,   302,   479,     3,     6,
     128,   130,   131,   183,   224,   480,   481,   482,   483,   485,
     478,   486,     4,   484,     3,     8,     4,   151,     4,   481,
       5,   150,     7,   487,   488,   489,     3,     6,   129,   132,
     133,   134,   490,   491,   492,   494,   495,   496,   488,   493,
       4,     4,     4,     3,     8,     4,   153,   151,   151,   491,
     150
  };

  const unsigned short int
  Dhcp6Parser::yyr1_[] =
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
     193,   193,   193,   194,   195,   196,   197,   198,   200,   199,
     202,   201,   203,   203,   204,   204,   206,   205,   207,   209,
     208,   211,   210,   212,   212,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   215,   214,
     216,   216,   216,   216,   218,   217,   220,   219,   222,   221,
     223,   225,   224,   226,   227,   228,   229,   231,   230,   233,
     232,   235,   234,   236,   236,   237,   237,   238,   239,   241,
     240,   242,   242,   243,   243,   243,   244,   245,   247,   246,
     249,   248,   250,   250,   251,   251,   253,   252,   255,   254,
     256,   256,   256,   257,   257,   259,   258,   261,   260,   263,
     262,   264,   264,   265,   265,   265,   265,   265,   265,   266,
     267,   268,   269,   270,   271,   273,   272,   274,   274,   275,
     275,   277,   276,   279,   278,   280,   280,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   283,   282,   285,   284,   287,   286,
     289,   288,   291,   290,   292,   292,   292,   293,   294,   296,
     295,   297,   297,   298,   298,   300,   299,   301,   301,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   304,   303,   305,   305,   306,   306,   308,
     307,   310,   309,   311,   311,   312,   312,   313,   313,   313,
     313,   313,   313,   313,   313,   314,   315,   316,   318,   317,
     320,   319,   322,   321,   323,   325,   324,   326,   328,   327,
     329,   329,   330,   330,   332,   331,   334,   333,   335,   335,
     336,   336,   337,   337,   337,   337,   337,   337,   337,   338,
     340,   339,   341,   342,   343,   344,   346,   345,   347,   347,
     348,   348,   350,   349,   352,   351,   353,   353,   354,   354,
     354,   354,   356,   355,   358,   357,   360,   359,   361,   361,
     362,   362,   364,   363,   366,   365,   367,   367,   368,   368,
     368,   368,   368,   368,   368,   368,   370,   369,   371,   373,
     372,   374,   375,   377,   376,   378,   378,   379,   379,   381,
     380,   383,   382,   384,   384,   385,   385,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   388,   387,   390,   389,
     392,   391,   394,   393,   396,   395,   398,   397,   400,   399,
     402,   401,   404,   403,   406,   405,   407,   407,   408,   288,
     409,   409,   410,   410,   411,   411,   411,   411,   412,   414,
     413,   416,   415,   417,   417,   418,   418,   418,   418,   418,
     418,   418,   420,   419,   421,   421,   421,   422,   424,   423,
     425,   426,   427,   429,   428,   430,   430,   431,   431,   433,
     432,   435,   434,   437,   436,   439,   438,   440,   440,   441,
     441,   441,   441,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   441,   442,   444,   443,   446,   445,   447,
     449,   448,   450,   451,   453,   452,   454,   454,   456,   455,
     457,   458,   459,   461,   460,   462,   462,   462,   462,   462,
     464,   463,   466,   465,   468,   467,   470,   469,   472,   471,
     473,   473,   474,   476,   475,   477,   477,   479,   478,   480,
     480,   481,   481,   481,   481,   481,   482,   484,   483,   486,
     485,   487,   487,   489,   488,   490,   490,   491,   491,   491,
     491,   493,   492,   494,   495,   496
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
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
       1,     1,     1,     3,     3,     3,     3,     3,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     0,
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
  "\"user-context\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"test\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "value", "sub_json", "map2", "$@13", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@14", "list_content",
  "not_empty_list", "list_strings", "$@15", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@16",
  "global_objects", "global_object", "dhcp6_object", "$@17", "sub_dhcp6",
  "$@18", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@19",
  "sub_interfaces6", "$@20", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@21", "re_detect",
  "lease_database", "$@22", "hosts_database", "$@23",
  "database_map_params", "database_map_param", "database_type", "$@24",
  "db_type", "user", "$@25", "password", "$@26", "host", "$@27", "port",
  "name", "$@28", "persist", "lfc_interval", "readonly", "connect_timeout",
  "contact_points", "$@29", "keyspace", "$@30", "mac_sources", "$@31",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@32",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@33",
  "hooks_libraries", "$@34", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@35",
  "sub_hooks_library", "$@36", "hooks_params", "hooks_param", "library",
  "$@37", "parameters", "$@38", "expired_leases_processing", "$@39",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@40",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@41",
  "sub_subnet6", "$@42", "subnet6_params", "subnet6_param", "subnet",
  "$@43", "interface", "$@44", "interface_id", "$@45", "client_class",
  "$@46", "reservation_mode", "$@47", "hr_mode", "id", "rapid_commit",
  "shared_networks", "$@48", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@49",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@50", "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@51", "sub_option_def", "$@52",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@53",
  "option_def_record_types", "$@54", "space", "$@55", "option_def_space",
  "option_def_encapsulate", "$@56", "option_def_array", "option_data_list",
  "$@57", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@58", "sub_option_data", "$@59",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@60",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@61", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@62", "sub_pool6", "$@63",
  "pool_params", "pool_param", "pool_entry", "$@64", "user_context",
  "$@65", "pd_pools_list", "$@66", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@67", "sub_pd_pool",
  "$@68", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@69",
  "pd_prefix_len", "excluded_prefix", "$@70", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@71", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@72", "sub_reservation",
  "$@73", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@74", "prefixes", "$@75", "duid",
  "$@76", "hw_address", "$@77", "hostname", "$@78", "flex_id_value",
  "$@79", "reservation_client_classes", "$@80", "relay", "$@81",
  "relay_map", "$@82", "client_classes", "$@83", "client_classes_list",
  "$@84", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@85",
  "server_id", "$@86", "server_id_params", "server_id_param",
  "server_id_type", "$@87", "duid_type", "htype", "identifier", "$@88",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@89",
  "control_socket_params", "control_socket_param", "socket_type", "$@90",
  "socket_name", "$@91", "dhcp_ddns", "$@92", "sub_dhcp_ddns", "$@93",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@94", "server_ip", "$@95", "server_port",
  "sender_ip", "$@96", "sender_port", "max_queue_size", "ncr_protocol",
  "$@97", "ncr_protocol_value", "ncr_format", "$@98",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@99", "replace_client_name_value",
  "generated_prefix", "$@100", "dhcp4_json_object", "$@101",
  "dhcpddns_json_object", "$@102", "control_agent_json_object", "$@103",
  "logging_object", "$@104", "logging_params", "logging_param", "loggers",
  "$@105", "loggers_entries", "logger_entry", "$@106", "logger_params",
  "logger_param", "debuglevel", "severity", "$@107", "output_options_list",
  "$@108", "output_options_list_content", "output_entry", "$@109",
  "output_params_list", "output_params", "output", "$@110", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short int
  Dhcp6Parser::yyrline_[] =
  {
       0,   235,   235,   235,   236,   236,   237,   237,   238,   238,
     239,   239,   240,   240,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   245,   246,   246,   254,   255,   256,   257,
     258,   259,   260,   263,   268,   268,   279,   282,   283,   286,
     290,   297,   297,   304,   305,   308,   312,   319,   319,   326,
     327,   330,   334,   345,   355,   355,   367,   368,   372,   373,
     374,   375,   376,   377,   380,   380,   397,   397,   405,   406,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   436,   441,   446,   451,   456,   461,   461,
     471,   471,   479,   480,   483,   484,   487,   487,   497,   503,
     503,   513,   513,   523,   524,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   542,   542,
     549,   550,   551,   552,   555,   555,   563,   563,   571,   571,
     579,   584,   584,   592,   597,   602,   607,   612,   612,   620,
     620,   629,   629,   639,   640,   643,   644,   647,   652,   657,
     657,   667,   668,   671,   672,   673,   676,   681,   688,   688,
     698,   698,   708,   709,   712,   713,   716,   716,   724,   724,
     732,   733,   734,   737,   738,   741,   741,   749,   749,   757,
     757,   767,   768,   771,   772,   773,   774,   775,   776,   779,
     784,   789,   794,   799,   804,   812,   812,   825,   826,   829,
     830,   837,   837,   860,   860,   869,   870,   874,   875,   876,
     877,   878,   879,   880,   881,   882,   883,   884,   885,   886,
     887,   888,   889,   890,   893,   893,   901,   901,   909,   909,
     917,   917,   925,   925,   932,   933,   934,   937,   942,   950,
     950,   961,   962,   966,   967,   970,   970,   978,   979,   982,
     983,   984,   985,   986,   987,   988,   989,   990,   991,   992,
     993,   994,   995,  1002,  1002,  1014,  1015,  1018,  1019,  1024,
    1024,  1035,  1035,  1045,  1046,  1049,  1050,  1053,  1054,  1055,
    1056,  1057,  1058,  1059,  1060,  1063,  1065,  1070,  1072,  1072,
    1080,  1080,  1088,  1088,  1096,  1098,  1098,  1106,  1115,  1115,
    1127,  1128,  1133,  1134,  1139,  1139,  1150,  1150,  1161,  1162,
    1167,  1168,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1182,
    1184,  1184,  1192,  1194,  1196,  1201,  1209,  1209,  1221,  1222,
    1225,  1226,  1229,  1229,  1237,  1237,  1245,  1246,  1249,  1250,
    1251,  1252,  1255,  1255,  1263,  1263,  1273,  1273,  1285,  1286,
    1289,  1290,  1293,  1293,  1301,  1301,  1309,  1310,  1313,  1314,
    1315,  1316,  1317,  1318,  1319,  1320,  1323,  1323,  1331,  1336,
    1336,  1344,  1349,  1357,  1357,  1367,  1368,  1371,  1372,  1375,
    1375,  1383,  1383,  1391,  1392,  1395,  1396,  1400,  1401,  1402,
    1403,  1404,  1405,  1406,  1407,  1408,  1411,  1411,  1421,  1421,
    1431,  1431,  1439,  1439,  1447,  1447,  1455,  1455,  1463,  1463,
    1476,  1476,  1486,  1486,  1497,  1497,  1507,  1508,  1511,  1511,
    1519,  1520,  1523,  1524,  1527,  1528,  1529,  1530,  1533,  1535,
    1535,  1546,  1546,  1556,  1557,  1560,  1561,  1562,  1563,  1564,
    1565,  1566,  1569,  1569,  1576,  1577,  1578,  1581,  1586,  1586,
    1594,  1599,  1606,  1613,  1613,  1623,  1624,  1627,  1628,  1631,
    1631,  1639,  1639,  1649,  1649,  1659,  1659,  1667,  1668,  1671,
    1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1681,
    1682,  1683,  1684,  1685,  1688,  1693,  1693,  1701,  1701,  1709,
    1714,  1714,  1722,  1727,  1732,  1732,  1740,  1741,  1744,  1744,
    1752,  1757,  1762,  1767,  1767,  1775,  1778,  1781,  1784,  1787,
    1793,  1793,  1803,  1803,  1810,  1810,  1817,  1817,  1830,  1830,
    1843,  1844,  1848,  1852,  1852,  1864,  1865,  1869,  1869,  1877,
    1878,  1881,  1882,  1883,  1884,  1885,  1888,  1893,  1893,  1901,
    1901,  1911,  1912,  1915,  1915,  1923,  1924,  1927,  1928,  1929,
    1930,  1933,  1933,  1941,  1946,  1951
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
#line 4391 "dhcp6_parser.cc" // lalr1.cc:1167
#line 1956 "dhcp6_parser.yy" // lalr1.cc:1168


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
